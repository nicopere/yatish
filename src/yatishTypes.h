/********************************************************************
 * Name:      yatishTypes.h
 * Purpose:   A few 'typedef' common to yatishPDF and yatishPlot
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2023-07-21
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

#ifndef YATISHTYPES_H
#define YATISHTYPES_H

#include <map>
#include <vector>

using namespace std;

typedef map <string, unsigned long> Map4pie;

/** Element of typefined std:vector RawData (yatishPlot.big_data). */
struct RawRecord {
    wxDateTime start, stop;
    wxString client, project, task, tool;
};
typedef vector <RawRecord> RawData;

/** Element of typefined std:vector ProcessedData (yatishPlot.data). */
struct ProcessedRecord {
    wxDateTime weekCenter;
    // various aggregates
    wxTimeSpan timeTotal, timeMax, timeRangeMax;
    int daysWorked;
    double minutesAtimeslot;
    // clusters (summing aggregate only)
    double hours [3]; /**< The highest three curves as determined by NoMoreThan4()
			   [except `_("others")`] for the current ClusterType.*/
};
typedef vector <ProcessedRecord> ProcessedData;

/** Same order as yatishFrame::choiceChart. */
enum PlotType {
    timeSeries,
    pieChart
};

/** Same order as yatishFrame::choiceAggregate (except `invalid` of course). */
enum AggregateType {
    invalid = -1,
    hoursTotal,
    daysWorked,
    hoursAdayMax,
    timeRangeMax,
    minutesAtimeslot
};

/** Same order as yatishFrame::choiceCluster.
 * \note Enumerator `none` a.k.a. `_("None")` must be the last one. */
enum ClusterType {
    clientClusters,
    projectClusters,
    taskClusters,
    toolClusters,
    none
};

#endif
