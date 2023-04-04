#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool fillSched(
    size_t row, 
    DailySchedule& sched, 
    const AvailabilityMatrix& avail, 
    vector<size_t>& shifts, 
    const size_t maxShifts,
    const size_t dailyNeed
    );

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    for (size_t i = 0; i < avail.size(); ++i) {
        std::vector<Worker_T> tempRow;
        sched.push_back(tempRow);
    }
    std::vector<size_t> shifts(avail[0].size());

    if (fillSched(0,sched,avail,shifts, maxShifts, dailyNeed)){
        // for (auto i:shifts){
        //     cout << i << endl;
        // }
        return true;
    }
    
    return false;
    

}

bool fillSched(size_t row, DailySchedule& sched, const AvailabilityMatrix& avail, vector<size_t>& shifts, const size_t maxShifts,const size_t dailyNeed){
    for (unsigned int i = 0; i < shifts.size(); ++i){
        if (row == avail.size()){
            return true;
        }
        if (avail[row][i] && shifts[i]<maxShifts && std::find(sched[row].begin(), sched[row].end(), i)==sched[row].end()){
            shifts[i]++;
            sched[row].push_back(i);
            if (sched[row].size()==dailyNeed){
                row++;
            }
            if (!fillSched(row,sched,avail,shifts, maxShifts, dailyNeed)){
                shifts[i]--;
                if (!sched[row].size()){
                    row--;
                }
                sched[row].pop_back();
            }
            else{
                return true;
            }
        }
    }
    return false;
}

