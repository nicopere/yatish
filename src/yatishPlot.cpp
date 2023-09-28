/********************************************************************
 * Name:      yatishPlot.cpp
 * Purpose:   Implements the (virtual) class for yatish data plots
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2023-07-05
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

#include "wx_pch.h"
#include "yatishPlot.h"

#define CHART_HEIGHT 250

//static members
ProcessedData yatishPlot::data;
string yatishPlot::legends [3];
vector<double> yatishPlot::vector_X, yatishPlot::vector_X2, yatishPlot::vector_Y [3];
bool yatishPlot::data_loaded = false;
RawData yatishPlot::big_data;

// colorbrewer2.org
wxColour colors[] = {
    wxColour (127, 201, 127),
    wxColour (190, 174, 212),
    wxColour (253, 192, 134),
    wxColour (255, 255, 153)
};

/** The constructor of yatishPlot:
 * - gets its RawData from yatishDBsqlite;
 * - computes the various aggregates.
 *
 * \note RawData are not updated during a given YATiSh run.
 */
yatishPlot::yatishPlot (yatishDBsqlite * pdb) {
    if (data_loaded) return;
    if ( !pdb->FillPlotData (big_data) )
        wxLogError ("Data loading failed (panel #3)");
    Aggregates();
    formerAggregate = invalid; // to force first PlotData()
    data_loaded = true;
    // vector_X and vector_X2 (prepared for plotting libraries) won't change in a given yatish run
    wxDateTime weekCenter;
    time_t epochTime;
    wxDateTime::wxDateTime_t weekNumber = 0, weekOffset = 0;
    for (ProcessedData::iterator it = data.begin(); it != data.end(); it++) {
        weekCenter = it->weekCenter;
        weekCenter.MakeFromUTC();                      // weekCenter: now localtime
        epochTime = weekCenter.GetTicks();
        vector_X.push_back (epochTime);                // auto-conversion: time_t->double
        if (weekCenter.GetWeekOfYear() < weekNumber)   // the year has changed
            weekOffset += weekNumber;
        weekNumber = weekCenter.GetWeekOfYear();
        vector_X2.push_back (weekNumber + weekOffset); // auto-conversion: wxDateTime_t->double
    }
}

/** Computes the week numbers corresponding to members `firstDay` and `lastDay`.
 * \param[inout] firstWeek week number corresponding to the current value of `firstDay`
 * \param[inout] lastWeek week number corresponding to the current value of `lastDay`
 * \note The algorithm is consistent with the one used by yatishPlot() for member `vector_X2`.
 */
void yatishPlot::GetWeekRange (unsigned int & firstWeek, unsigned int & lastWeek) {
    wxDateTime weekCenter;
    wxDateTime::wxDateTime_t weekNumber = 0, weekOffset = 0,
                             firstOffset = 0, lastOffset = 0; // to get rid of a warning
    int yearCenter, firstYear = firstDay.GetYear(), lastYear = lastDay.GetYear();
    for (ProcessedData::size_type j = 0; j < data.size(); j++) {
        weekCenter = data[j].weekCenter;
        if (weekCenter.GetWeekOfYear() < weekNumber) weekOffset += weekNumber;
        weekNumber = weekCenter.GetWeekOfYear();
        yearCenter = weekCenter.GetYear();
        if (yearCenter == firstYear) firstOffset = weekOffset;
        if (yearCenter == lastYear ) lastOffset  = weekOffset;
        if (yearCenter >= firstYear && yearCenter >= lastYear) break;
    }
    if (firstDay.GetMonth() == wxDateTime::Jan && firstDay.GetDay() == 1)
        firstWeek = 1.; // first of January is likely to belong to the last week of the previous year
    else
        firstWeek = firstDay.GetWeekOfYear();
    firstWeek += firstOffset;
    lastWeek = lastDay.GetWeekOfYear() + lastOffset;
}

/** Builds all the _weekly_ time series (non-clustered aggregates).
 * \note Local variable `big_data` was ordered by increasing Record.start
 * thanks to yatishDBsqlite::FillPlotData(). No time window here.
 */
void yatishPlot::Aggregates() {
    int offset = -1;
    wxDateTime::wxDateTime_t currentWeek = 0;
    wxDateTime::WeekDay currentDay = wxDateTime::Inv_WeekDay;

    wxDateTime start, stop, firstStartDaily, emptyWeek;
    wxTimeSpan span, timeDaily, timeRangeDaily, noTime = wxTimeSpan::Hours (0);
    int recordCount = 0;
    ProcessedRecord a, b;
    for (RawData::iterator it = big_data.begin(); it != big_data.end(); it++) {
        start = it->start; stop = it->stop; span = stop - start;
        if (start.GetWeekOfYear() == currentWeek) {
            data[offset].timeTotal += span;
            data[offset].minutesAtimeslot = data[offset].timeTotal.GetSeconds().ToDouble()/++recordCount/60.;
            if (start.GetWeekDay() == currentDay) {
                timeDaily += span;
                // assuming Records are not overlapping (i.e. Record.stop keeps increasing)
                timeRangeDaily = stop - firstStartDaily;
            } else {
                data[offset].daysWorked++;
                timeDaily = span;
                firstStartDaily = start; timeRangeDaily = stop - firstStartDaily;
                currentDay = start.GetWeekDay();
            }
            if (data[offset].timeMax      < timeDaily     ) data[offset].timeMax      = timeDaily;
            if (data[offset].timeRangeMax < timeRangeDaily) data[offset].timeRangeMax = timeRangeDaily;
        } else { // including first iteration
            timeDaily = span;
            firstStartDaily = start; timeRangeDaily = stop - firstStartDaily;
            currentDay = start.GetWeekDay();
            start.SetToWeekDayInSameWeek (wxDateTime::Thu); start.ResetTime(); start.SetHour (12);
            a.weekCenter = start;
            a.timeTotal = span;
            a.daysWorked = 1;
            a.timeMax = span;
            a.timeRangeMax = stop - firstStartDaily;
            a.minutesAtimeslot = span.GetSeconds().ToDouble()/60.;
            if (currentWeek > 0) { // excluding first iteration
                emptyWeek = data[offset].weekCenter + wxDateSpan::Week();
                while ( emptyWeek.IsEarlierThan (a.weekCenter) ) { // fill in empty values if need be
                    b.weekCenter = emptyWeek;
                    b.timeTotal = noTime;
                    b.daysWorked = 0;
                    b.timeMax = noTime;
                    b.timeRangeMax = noTime;
                    b.minutesAtimeslot = 0.;
                    data.push_back (b); offset++;
                    emptyWeek += wxDateSpan::Week();
                }
            }
            data.push_back (a); offset++;
            currentWeek = start.GetWeekOfYear();
            recordCount = 1;
        }
    }
}

/** Fills member `pieData` with data for a pie chart with 4 sectors.
 * Only the records between `firstday` and `lastDay` are considered.
 * \param[in] clusters any value __except `none`__
 * \note Also used by ClusteredSeries(), to choose the 3 most significant time series and get their `legend`.
 */
void yatishPlot::ComputePie (ClusterType clusters) {
    pieData.clear();
    // Compute total time per cluster; each timeslot is rounded down to the minute:
    wxDateTime start;
    wxTimeSpan span;
    unsigned long minutes;
    string key;
    wxASSERT (clusters != none);
    for (RawData::iterator it = big_data.begin(); it != big_data.end(); it++) {
        start = it->start;
        if (start < firstDay || start > lastDay) continue;
        span = it->stop - start;
        minutes = span.GetHours()*60 + span.GetMinutes();
        switch (clusters) {
            case clientClusters:
                key = it->client .ToStdString();
                break;
            case projectClusters:
                key = it->project.ToStdString();
                break;
            case taskClusters:
                key = it->task   .ToStdString();
                break;
            default: //toolClusters
                key = it->tool   .ToStdString();
        }
        pieData[key] += minutes;
    }
    NoMoreThan4();
    // Store the largest cluster names (drop "others"):
    Map4pie::iterator it; int i;
    for (i = 0; i < 3; i++)
        legends[i].clear();
    string others = _("others").ToStdString();
    for (it = pieData.begin(), i = 0; it != pieData.end(); it++)
        if (it->first != others)
            legends[i++] = it->first;
}

/** Modifies member `pieData` so that there is no more than four record.
    Creates _or rename_ an `others` key, which contains the _smallest_ item(s).
 */
void yatishPlot::NoMoreThan4 () {
    unsigned long mini;
    string key, others = _("others").ToStdString();
    if (pieData.size() == 4) { // we need to label the smallest as "others" because there will be only 3 curves anyway
        mini = ULONG_MAX;
        for (auto element : pieData)
            if (element.second < mini) {
                mini = element.second;
                key = element.first;
            }
        pieData[others] = mini;
        pieData.erase (pieData.find (key) );
    }
    while (pieData.size() > 4) {
        mini = ULONG_MAX;
        for (auto element : pieData) {
            if (element.first == others) continue;
            if (element.second < mini) {
                mini = element.second;
                key = element.first;
            }
        }
        pieData[others] += mini;
        pieData.erase (pieData.find (key) );
    }
}

/** Creates a _wxString_ with the total hours in the current pie chart.
 * To be used by derived classes willing to overload the default TotalFormatted()
 * [which returns a _wxEmptyString_].
 */
wxString yatishPlot::TotalFormattedFromPie () {
    unsigned long totalMinutes = 0;
    for (auto element : pieData)
        totalMinutes += element.second;
    double totalHours = totalMinutes/60.;
    double totalDays = totalHours/7.;
    return wxString::Format(_("SUM: %.1f hours (%.1f days)"), totalHours, totalDays);
}

/** Updates the clustered time series. No time filtering here,
 * but the curves are selected according to Pies() which does take the date range into account.
 * \note The time axis (weekCenter) is already there thanks to Aggregates() which was called by the constructor.
 */
void yatishPlot::ClusteredSeries (ClusterType clusters) {
    int offset = -1;
    wxDateTime::wxDateTime_t currentWeek = 0;
    wxDateTime start;
    wxTimeSpan span, noTime = wxTimeSpan::Hours (0);
    double span_hours;
    string s;
    int i, j;

    wxASSERT (clusters != none);
    for (RawData::iterator it = big_data.begin(); it != big_data.end(); it++) {
        start = it->start;
        span = it->stop - start;
        span_hours = span.GetSeconds().ToDouble()/3600.;
        switch (clusters) {
            case clientClusters:
                s = it->client .ToStdString();
                break;
            case projectClusters:
                s = it->project.ToStdString();
                break;
            case taskClusters:
                s = it->task   .ToStdString();
                break;
            default: //toolClusters
                s = it->tool   .ToStdString();
        }
        i = 0;
        while (s != legends[i] && i < 3) i++;
        if (start.GetWeekOfYear() == currentWeek) {
            if (i < 3) data[offset].hours[i] += span_hours;
        } else { // including first iteration
            currentWeek = start.GetWeekOfYear();
            do offset++;
            while (data[offset].timeTotal == noTime); // skip eventual empty weeks
            for (j = 0; j < 3; j++) data[offset].hours[j] = 0.;
            if (i < 3) data[offset].hours[i] = span_hours;
        }
    }
}

/** Updates `vector_Y[3]` if need be (for the plotting libraries).
 * \return `true` if nothing else to be done (`false` if replot is needed)
 * \note calls virtual methods SetRangeX() and ClearCurves()
 */
bool yatishPlot::SelectData (ClusterType clusters, AggregateType aggregate) {
    if (clusters != none) { // modify the choice of clustered series [through Pies()]
        ComputePie (clusters);
        ClusteredSeries (clusters);
    }
    if (clusters == none && aggregate == formerAggregate) { // nothing to do apart from setting X range
        SetRangeX();
        return true;
    }

    for (int i = 0; i < 3; i++)
        vector_Y[i].clear();
    ClearCurves();

    ProcessedData::iterator it;
    wxASSERT (aggregate != invalid);
    if (clusters == none) {
        for (it = data.begin(); it != data.end(); it++) {
            switch (aggregate) {
                case hoursTotal:
                    vector_Y[0].push_back (it->timeTotal.GetSeconds().ToDouble()/3600.);
                    break;
                case daysWorked:
                    vector_Y[0].push_back ((double)it->daysWorked);
                    break;
                case hoursAdayMax:
                    vector_Y[0].push_back (it->timeMax.GetSeconds().ToDouble()/3600.);
                    break;
                case timeRangeMax:
                    vector_Y[0].push_back (it->timeRangeMax.GetSeconds().ToDouble()/3600.);
                    break;
                default: //minutesAtimeslot
                    vector_Y[0].push_back (it->minutesAtimeslot);
            }
        }
        formerAggregate = aggregate;
    } else {
        for (it = data.begin(); it != data.end(); it++)
            for (int i = 0; i < 3; i++)
                vector_Y[i].push_back (it->hours[i]);
        formerAggregate = invalid;
    }

    return false;
}

/***************************
 Graphic library: wxMathPlot
 ***************************/

yatishMathPlot::yatishMathPlot (wxWindow * p, yatishDBsqlite * pdb)
              : yatishPlot (pdb), mpWindow (p, wxID_ANY) {
    SetMinSize ( wxSize (-1, CHART_HEIGHT) );
    Xaxis = new mpScaleX (_("weeks"), mpALIGN_BORDER_BOTTOM, true, mpX_DATE);
    AddLayer (Xaxis, false);
    Yaxis = new mpScaleY (_("hours"), mpALIGN_BORDER_LEFT);
    AddLayer (Yaxis, false);
    //SetMargins (0, 0, 0, 0);
    EnableDoubleBuffer (true);
    wxPen pen [3] = { *wxBLUE_PEN, *wxGREEN_PEN, *wxRED_PEN };
    wxString title;
    for (int i = 0; i < 3; i++) {
        title.Printf ("vector1%d", i);
        vector1[i] = new mpFXYVector (title); // initial title otherwise mpInfoLegend gets confused
        vector1[i]->SetContinuity (true);
        title.Printf ("vector2%d", i);
        vector2[i] = new mpFXYVector (title);
        pen[i].SetWidth (5); vector2[i]->SetPen (pen[i]);
        AddLayer (vector1[i], false);
        AddLayer (vector2[i], false);
    }
    int w, h;
    p->GetSize (&w, &h);
    legend = new mpInfoLegend ( wxRect (w/2, 0, 50, 50) );
    legend->SetItemMode (mpLEGEND_SQUARE);
    AddLayer (legend);
    legend->SetVisible (true);
}

void yatishMathPlot::PlotData (ClusterType clusters, AggregateType aggregate) {
    if ( SelectData (clusters, aggregate) ) return;
    if (clusters == none) {
        wxASSERT ( vector_X.size() == vector_Y[0].size() );
        vector1[0]->SetData (vector_X, vector_Y[0]);
        vector2[0]->SetData (vector_X, vector_Y[0]);
        vector1[0]->SetVisible (true);
        vector2[0]->SetVisible (true);
        for (int i = 1; i < 3; i++) {
            vector1[i]->SetVisible (false);
            vector2[i]->SetVisible (false);
        }
        legend->SetVisible (false);
        if (aggregate == daysWorked)
            Yaxis->SetName(_("days") );
        else if (aggregate == minutesAtimeslot)
            Yaxis->SetName(_("minutes") );
        else
            Yaxis->SetName(_("hours") );
    } else {
        for (int i = 0; i < 3 && legends[i].size(); i++) {
            vector1[i]->SetData (vector_X, vector_Y[i]);
            vector2[i]->SetData (vector_X, vector_Y[i]);
            vector1[i]->SetName ( wxString (legends[i]) ); // wxEmptyString confuses mpInfoLegend
            vector2[i]->SetName ( wxString (legends[i]) );
            vector1[i]->SetVisible (true);
            vector2[i]->SetVisible (true);
        }
        legend->SetVisible (true);
        Yaxis->SetName(_("hours") );
    }
    SetRangeX();
}

void yatishMathPlot::SetRangeX () {
    UpdateBBox(); // mpWindow::m_minY and mpWindow::m_maxY are set there
    Fit (firstDay.GetTicks(), lastDay.GetTicks() + 86400, m_minY, m_maxY); // auto-conversion: time_t->double
}

void yatishMathPlot::ClearCurves () {
   for (int i = 0; i < 3; i++) {
        vector1[i]->Clear(); vector1[i]->SetVisible (false);
        vector2[i]->Clear(); vector2[i]->SetVisible (false);
   }
}

/****************************
 Graphic library: wxFreeChart
 ****************************/

yatishFreeSerie::yatishFreeSerie (wxWindow * p, yatishDBsqlite * pdb)
               : yatishPlot (pdb), wxChartPanel (p) {
    SetMinSize ( wxSize (-1, CHART_HEIGHT) );
#ifdef wxUSE_GRAPHICS_CONTEXT
    SetAntialias(true);
#endif
    dataset = new XYSimpleDataset();
    wxVector<wxRealPoint> vector_XY [3]; // we need a few temporary points to start with
    for (int i = 0; i < 3; i++) {
        vector_XY[i].push_back (wxRealPoint (1, i  ) );
        vector_XY[i].push_back (wxRealPoint (2, i+1) );
        series[i] = new XYSerie (vector_XY[i]);
        series[i]->SetName ( wxString::Format ("#%d", i) ); // temporary name
        dataset->AddSerie (series[i]);
    }
    renderer = new XYLineRenderer (true, true);
    renderer->SetSeriePen ( 0, wxThePenList->FindOrCreatePen (*wxBLUE,  2, wxPENSTYLE_SOLID) );
    renderer->SetSeriePen ( 1, wxThePenList->FindOrCreatePen (*wxGREEN, 2, wxPENSTYLE_SOLID) );
    renderer->SetSeriePen ( 2, wxThePenList->FindOrCreatePen (*wxRED,   2, wxPENSTYLE_SOLID) );
    dataset->SetRenderer (renderer);
    plot = new XYPlot();
    plot->AddDataset (dataset);
    leftAxis   = new NumberAxis (AXIS_LEFT);
    bottomAxis = new NumberAxis (AXIS_BOTTOM);
    leftAxis  ->SetTickFormat ("%.0f");
    bottomAxis->SetTickFormat ("%.0f");
    bottomAxis->ZeroOrigin (false);
    bottomAxis->SetTitle (_("weeks") );
    plot->AddAxis (leftAxis);
    plot->AddAxis (bottomAxis);
    plot->LinkDataVerticalAxis   (0, 0);
    plot->LinkDataHorizontalAxis (0, 0);
    legend = new Legend (wxCENTER, wxRIGHT);
    plot->SetLegend (legend);
    chart = new Chart(plot, NULL, NULL);
    SetChart (chart);
}

void yatishFreeSerie::PlotData (ClusterType clusters, AggregateType aggregate) {
    if ( SelectData (clusters, aggregate) ) return;
    if (clusters == none) {
        wxASSERT ( vector_X2.size() == vector_Y[0].size() );
        for (ProcessedData::size_type j = 0; j < vector_X.size(); j++)
            series[0]->Append ( wxRealPoint (vector_X2[j], vector_Y[0][j]) );
        if (aggregate == daysWorked)
            leftAxis->SetTitle(_("days") );
        else if (aggregate == minutesAtimeslot)
            leftAxis->SetTitle(_("minutes") );
        else
            leftAxis->SetTitle(_("hours") );
    } else {
        for (int i = 0; i < 3 && legends[i].size(); i++) {
            for (ProcessedData::size_type j = 0; j < vector_X2.size(); j++)
                series[i]->Append ( wxRealPoint (vector_X2[j], vector_Y[i][j]) );
            series[i]->SetName ( wxString (legends[i]) );
        }
        leftAxis->SetTitle(_("hours") );
    }
    SetRangeX();
    dataset->DatasetChanged();
}

void yatishFreeSerie::SetRangeX () {
    unsigned int firstWeek, lastWeek;
    GetWeekRange (firstWeek, lastWeek);
    bottomAxis->SetFixedBounds (firstWeek, lastWeek); // unsigned int -> double
    dataset->DatasetChanged();
}

void yatishFreeSerie::ClearCurves () {
    int i; size_t j;
    for (i = 0; i < 3; i++) {
        j = series[i]->GetCount();
        while (j > 0) series[i]->Remove (--j);
        series[i]->SetName (" ");
    }
}

yatishFreePie::yatishFreePie (wxWindow * p, yatishDBsqlite * pdb)
             : yatishPlot (pdb), wxChartPanel (p) {
    SetMinSize ( wxSize (-1, CHART_HEIGHT) );
#ifdef wxUSE_GRAPHICS_CONTEXT
    SetAntialias(true);
#endif
    dataset = new CategorySimpleDataset (categories, 4);
    dataset->AddSerie (wxEmptyString, data, 4);
    colorScheme = new ColorScheme ( colors, WXSIZEOF(colors) );
    renderer = new CategoryRenderer (*colorScheme);
    dataset->SetRenderer (renderer);
    plot = new PiePlot();
    plot->SetColorScheme (colorScheme);
    plot->SetDataset (dataset);
    legend = new Legend (wxCENTER, wxRIGHT);
    plot->SetLegend (legend);
    chart = new Chart(plot, NULL, NULL);
    SetChart (chart);
}

void yatishFreePie::PlotData (ClusterType clusters, AggregateType aggregate) {
    wxASSERT (clusters != none);
    ComputePie (clusters);
    Map4pie::iterator it; int i;
    for (i = 0; i < 4; i++) {
        categories[i] = wxEmptyString;
        data[i] = 0.;
    }
    for (it = pieData.begin(), i = 0; it != pieData.end(); it++) {
        categories[i] = wxString (it->first);
        data[i++] = it->second;
    }
    dataset = new CategorySimpleDataset (categories, 4);
    dataset->AddSerie (wxEmptyString, data, 4);
    dataset->SetRenderer (renderer);
    plot->SetDataset (dataset); // ~CategorySimpleDataset [and thus ~Dataset()] are called here
    dataset->DatasetChanged();
}

/*************************
 Graphic library: wxCharts
 *************************/

yatishChartSerie::yatishChartSerie (wxWindow * p, yatishDBsqlite * pdb)
                : yatishPlot (pdb), wxPanel (p) {
    SetMinSize ( wxSize (-1, CHART_HEIGHT) );
    panelSizer = new wxBoxSizer (wxHORIZONTAL);
    SetSizer (panelSizer);
    lineChartON = legendON = false;
}

void yatishChartSerie::PlotData (ClusterType clusters, AggregateType aggregate) {
    currentClusters = clusters;
    ResetChart(); // with this library we must recreate everything anyway
    if ( SelectData (clusters, aggregate) ) return;
    for (ProcessedData::size_type j = 0; j < vector_X.size(); j++) {
        labels.push_back ( wxString::Format ("%.0f", vector_X2[j]) );
        if (clusters == none)
            points[0].push_back (vector_Y[0][j]);
        else
            for (int i = 0; i < 3 && legends[i].size(); i++)
                points[i].push_back (vector_Y[i][j]);
    }
    CreateChart();
}

void yatishChartSerie::ResetChart () {
    if (legendON) {
        panelSizer->Detach (legendCtrl);
        legendCtrl->Destroy();
        legendON = false;
    }
    if (lineChartON) {
        panelSizer->Detach (lineChartCtrl);
        lineChartCtrl->Destroy();
        lineChartON = false;
    }
    for (int i = 0; i < 3; i++) {
        dataset[i].reset(); // => delete data[i] (?) [when dataset[i].use_count() = 0]
        points[i].clear();
    }
    labels.clear();
    chartData.reset();
}

void yatishChartSerie::CreateChart () {
    chartData = wxChartsCategoricalData::make_shared (labels);
    if (currentClusters == none) {
        data[0] = new wxChartsDoubleDataset (wxEmptyString, points[0]);
        dataset[0].reset (data[0]);
        chartData->AddDataset (dataset[0]);
    } else
        for (int i = 0; i < 3 && legends[i].size(); i++) {
            data[i] = new wxChartsDoubleDataset (wxString (legends[i]), points[i]);
            dataset[i].reset (data[i]);
            chartData->AddDataset (dataset[i]);
        }
    lineChartCtrl = new wxLineChartCtrl (this, wxID_ANY, chartData, wxCHARTSLINETYPE_STRAIGHT,
                                         wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    panelSizer->Add (lineChartCtrl, 5, wxEXPAND);
    lineChartON = true;
    if (currentClusters != none) {
        wxChartsLegendData legendData ( chartData->GetDatasets() );
        legendCtrl = new wxChartsLegendCtrl (this, wxID_ANY, legendData,
                                             wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
        panelSizer->Add (legendCtrl, 1, wxEXPAND);
        legendON = true;
    }
    panelSizer->Fit (this);
}

void yatishChartSerie::SetRangeX () {
    ResetChart(); // with this library we must recreate everything anyway
    unsigned int firstWeek, lastWeek;
    GetWeekRange (firstWeek, lastWeek);
    for (ProcessedData::size_type j = 0; j < vector_X.size(); j++) {
        if (vector_X2[j] < firstWeek) continue;
        if (vector_X2[j] > lastWeek) break;
        labels.push_back ( wxString::Format ("%.0f", vector_X2[j]) );
        if (currentClusters == none)
            points[0].push_back (vector_Y[0][j]);
        else
            for (int i = 0; i < 3 && legends[i].size(); i++)
                points[i].push_back (vector_Y[i][j]);
    }
    CreateChart();
}

yatishChartPie::yatishChartPie (wxWindow * p, yatishDBsqlite * pdb)
              : yatishPlot (pdb), wxPanel (p) {
    SetMinSize ( wxSize (-1, CHART_HEIGHT) );
    panelSizer = new wxBoxSizer (wxHORIZONTAL);
    SetSizer (panelSizer);
    pieChartON = legendON = false;
}

void yatishChartPie::PlotData (ClusterType clusters, AggregateType aggregate) {
    ResetChart(); // UpdateSlices() won't change labels :-(
    chartData = wxPieChartData::make_shared();
    ComputePie (clusters);
    Map4pie::iterator it; int i;
    for (it = pieData.begin(), i = 0; it != pieData.end(); it++)
        slices.push_back ( wxChartSliceData ( it->second, colors[i++], wxString (it->first) ) );
    chartData->AddSlices (slices);
    pieChartCtrl = new wxPieChartCtrl (this, wxID_ANY, chartData,
                                       wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    pieChartON = true;
    wxChartsLegendData legendData ( chartData->GetSlices() );
    legendCtrl = new wxChartsLegendCtrl(this, wxID_ANY, legendData,
                                        wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    legendON = true;
    panelSizer->Add (pieChartCtrl, 5, wxEXPAND);
    panelSizer->Add (legendCtrl, 1, wxEXPAND);
    panelSizer->Fit (this);
}

void yatishChartPie::ResetChart () {
    if (legendON) {
        panelSizer->Detach (legendCtrl);
        legendCtrl->Destroy();
        legendON = false;
    }
    if (pieChartON) {
        panelSizer->Detach (pieChartCtrl);
        pieChartCtrl->Destroy();
        pieChartON = false;
    }
    slices.clear();
    chartData.reset();
}
