/********************************************************************
 * Name:      yatishPlot.h
 * Purpose:   Declares the (virtual) class for yatish data plots
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2023-07-05
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

#ifndef YATISHPLOT_H
#define YATISHPLOT_H

#include "yatishDBsqlite.h"
#include "yatishTypes.h"

/** Abstract Base class for the plots of panel #3.
 * The times series are compiled on a __weekly__ basis.
 *
 * They are either "aggregated" (only one curve is shown at any time):
 * - hours (total)
 * - days (worked)
 * - hours/day (max)
 * - time range (max)
 * - minutes/timeslot (mean)
 *
 * or "clustered" (the 3 most significant curves are shown):
 * - clients
 * - projects
 * - tasks
 * - tools
 *
 * and in the latter case the relevant aggregate is "hours (total)" [per week].
 */
class yatishPlot {
    public:
        yatishPlot (yatishDBsqlite *);
        virtual ~yatishPlot () {}
        void SetFirstDay (const wxDateTime& dt) { firstDay = dt; }
        void SetLastDay  (const wxDateTime& dt) { lastDay  = dt; }
        /** Plotting interface for yatishFrame:
         * - computes data that depends on the time window;
         * - updates the plot selected by the user (in controls of panel #3).
         *
         * \param[in] clusters the clusters to compute and show; default: `none`
         * \param[in] aggregate if clusters are not used, the aggregate to show; default: `hoursTotal`
         * \note PlotData() is supposed to be called when something has changed (at least the time window).
         * \todo runtime instability when `clusters == tools` or when switching back from pie chart
         * (debug mode), although no problem was debugger detected in ComputePie() nor ClusteredSeries()
         * \todo default plot (timeSeries/hoursTotal/none) sometimes empty when changing library in settings
         * (need to play with aggregate choice to recover it)
         */
        virtual void PlotData (ClusterType, AggregateType) = 0;
        virtual wxString TotalFormatted () {return wxEmptyString;}
    protected:
        static ProcessedData data; /**< weekly times series: various aggregates and clustered sums */
        static string legends [3]; /**< names of the 3 weekly clustered sums, for the current clustering scheme */
        static vector<double> vector_X,     /**< epoch time */
                              vector_X2,    /**< week number, counted from the first year in the time series */
                              vector_Y [3]; /**< user selected data */
        Map4pie pieData; /**< total durations (between `firstDay` and `lastDay`), in minutes */
        wxDateTime firstDay, lastDay;
        AggregateType formerAggregate;
        void GetWeekRange (unsigned int &, unsigned int &);
        void ComputePie (ClusterType);
        wxString TotalFormattedFromPie ();
        bool SelectData (ClusterType, AggregateType);
        virtual void SetRangeX () {}
        virtual void ClearCurves () {}
    private:
        static bool data_loaded;
        static RawData big_data; /**< all timeslot records from the database */
        void Aggregates ();
        void NoMoreThan4 ();
        void ClusteredSeries (ClusterType);
};

/** Time series for panel #3 using [wxMathPlot](https://sourceforge.net/projects/wxmathplot/).
 * \note This library can't do pie charts.
 */
class yatishMathPlot: public yatishPlot, public mpWindow {
    public:
        yatishMathPlot (wxWindow *, yatishDBsqlite *);
        void PlotData (ClusterType, AggregateType);
    private:
        mpFXYVector * vector1 [3], * vector2 [3];
        mpScaleX * Xaxis;
        mpScaleY * Yaxis;
        mpInfoLegend * legend;
        void SetRangeX ();
        void ClearCurves ();
};

/** Time series for panel #3 using [wxFreeChart](https://github.com/iwbnwif/wxFreeChart.git).
 * \note Could not use TimeSeriesDataset because it lacks a AddSerie() (and Legend management),
 * hence a XYSimpleDataset with a home-baked week number (increasing from year to year).
 */
class yatishFreeSerie: public yatishPlot, public wxChartPanel {
    public:
        yatishFreeSerie (wxWindow *, yatishDBsqlite *);
        void PlotData (ClusterType, AggregateType);
    private:
        XYSimpleDataset * dataset;
        XYSerie * series [3];
        XYLineRenderer * renderer;
        XYPlot * plot;
        NumberAxis * leftAxis, * bottomAxis;
        Legend * legend;
        Chart * chart;
        void SetRangeX ();
        void ClearCurves ();
};

/** Pie chart for panel #3 using [wxFreeChart](https://github.com/iwbnwif/wxFreeChart.git).
 * \note `PiePlot` class documentation: "TODO: initial quick and dirty, must be cleaned up or rewritten."
 */
class yatishFreePie: public yatishPlot, public wxChartPanel {
    public:
        yatishFreePie (wxWindow *, yatishDBsqlite *);
        void PlotData (ClusterType, AggregateType);
        wxString TotalFormatted () {return TotalFormattedFromPie();}
    private:
        wxString categories [4];
        double data [4];
        CategorySimpleDataset * dataset;
        ColorScheme * colorScheme;
        CategoryRenderer * renderer;
        PiePlot * plot;
        Legend * legend;
        Chart * chart;
};

/** Time series for panel #3 using [wxCharts](https://github.com/wxIshiko/wxCharts).
 * \note Nice plots but poor interface: must (re)create everything to modify a plot.
 * \note No `data` argument in wxTimeSeriesChartCtrl() [=>sample _timeseries_ is empty!],
 * hence a wxLineChartCtrl using week number on the bottom axis.
 * \sa yatishFreeSerie
 */
class yatishChartSerie: public yatishPlot, public wxPanel {
    public:
        yatishChartSerie (wxWindow *, yatishDBsqlite *);
        void PlotData (ClusterType, AggregateType);
    private:
        wxBoxSizer * panelSizer;
        wxVector<wxString> labels;
        wxVector<wxDouble> points [3];
        wxChartsCategoricalData::ptr chartData;
        wxChartsDoubleDataset * data [3];
        wxChartsDoubleDataset::ptr dataset [3];
        wxLineChartCtrl * lineChartCtrl;
        wxChartsLegendCtrl * legendCtrl;
        bool lineChartON, legendON;
        ClusterType currentClusters;
        void ResetChart ();
        void CreateChart ();
        void SetRangeX ();
};

/** Pie chart for panel #3 using [wxCharts](https://github.com/wxIshiko/wxCharts).
 */
class yatishChartPie: public yatishPlot, public wxPanel {
    public:
        yatishChartPie (wxWindow *, yatishDBsqlite *);
        void PlotData (ClusterType, AggregateType);
        wxString TotalFormatted () {return TotalFormattedFromPie();}
    private:
        wxBoxSizer * panelSizer;
        wxPieChartData::ptr chartData;
        wxVector <wxChartSliceData> slices;
        wxPieChartCtrl * pieChartCtrl;
        wxChartsLegendCtrl * legendCtrl;
        bool pieChartON, legendON;
        void ResetChart ();
};
#endif // YATISHPLOT_H
