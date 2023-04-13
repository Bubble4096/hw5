#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
// bool isValid(AvailabilityMatrix &avail, DailySchedule &sched, vector<int> numShiftsTracker, int worker_id, int max_shifts, int day, int shift_num);
// bool schedule_helper( AvailabilityMatrix &avail, const size_t dailyNeed, const size_t maxShifts, vector<int> &NumShiftsTracker, DailySchedule &sched, int day, int worker_num, int shift_num);
// bool schedule(const AvailabilityMatrix &avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule &sched);

// Add your implementation of schedule() and other helper functions here

bool isValid(AvailabilityMatrix avail, DailySchedule& sched, vector<size_t> NumShiftsTracker, Worker_T worker_id, const size_t max_shifts, int day, int shift_num)
{
    // Case #1 worker available for shift
    if (avail[day][worker_id] != 1)
    {
        return false;
    }
    // Case #2 worker under max shifts
    if (NumShiftsTracker[worker_id] >= max_shifts)
    {
        return false;
    }

    // Case #3 worker not working that same day
    for (int  p = 0; p < shift_num; p++)
    {
        cout << endl << "ENTERING SAME DAY SCHEDULING" << endl << endl;
        cout<< "p: " <<  p << endl;
        cout<< "shift: " << shift_num << endl;
        if (sched[day][p] == worker_id)
        {
            return false;
        }
    }

    return true;
}

bool schedule_helper(AvailabilityMatrix avail, const size_t dailyNeed, const size_t maxShifts, vector<size_t> NumShiftsTracker, DailySchedule &sched, int day, Worker_T worker_num, int shift_num, int tries)

{
    cout << "entered schedule helper" << endl;
    // checck worker num
    if (worker_num >= (avail.size()))
    {

       /* for(size_t x = 0; x < 3; x++)
        {
          bool frfr;
          frfr = schedule_helper(avail, dailyNeed, maxShifts, NumShiftsTracker, sched, --day, static_cast<Worker_T>(x), shift_num, tries== true);
        
          if(frfr == true)
          {
            return true;
          } 
          else
          {
            return false;
          }
        }
        */
     return false;
     

    }
    // id day = avail size , return true
    if (day == static_cast<int>(avail.size()))
    {
        cout << "Case 0" << endl;
        return true;
    }

    // Case 1: End of scheduling, move on to next day
    if (int(shift_num) == int(dailyNeed))
    {
        cout << "Case 1" << endl;
        // call schedule helper

        day++;          // new day
        worker_num = 0; // worker 0
        shift_num = 0;  // shift 0,

        return schedule_helper(avail, dailyNeed, maxShifts, NumShiftsTracker, sched, day, worker_num, shift_num, tries);
    }

    // Case #2  needs worker and worker is availabile
    Worker_T worker_id_copy = worker_num;
    const size_t max_shifts_copy = maxShifts;
    int day_copy = day;
    DailySchedule sched_copy = sched;

    bool validity = isValid(avail, sched_copy, NumShiftsTracker, worker_id_copy, max_shifts_copy, day_copy, shift_num);
    
    if (validity == true)
    {
        cout << "Case 2" << endl;
        sched[day][shift_num] = worker_num;
        cout << "added worker: " << worker_num << endl << "to day: " << day << endl << "shift: " << shift_num << endl;
        NumShiftsTracker[worker_num]++; // increase number of shifts for worker
        
        if (schedule_helper(avail, dailyNeed, maxShifts, NumShiftsTracker, sched, day, 0, (++shift_num), tries) == true)
        {
            return true;
        }
        else
        {
            sched[day][shift_num] = INVALID_ID;
            NumShiftsTracker[worker_num]--;
            tries++;

            schedule_helper(avail, dailyNeed, maxShifts, NumShiftsTracker, sched, day, --worker_num, (shift_num), tries);
        }
    }
    // Case #3  needs worker and worker is not availabile
    cout << "Case 3" << endl;
    if(worker_num == 3 && tries < 3)
    {
        worker_num = 0;
        tries++;
    } 
    else{
        worker_num++;
        tries++;
    }
    
    return schedule_helper(avail, dailyNeed, maxShifts, NumShiftsTracker, sched, day, worker_num, shift_num, tries); // chedu
}

bool schedule(const AvailabilityMatrix &avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule &sched)
{
    cout << "entering schedule function" << endl;
    if (avail.size() == 0U)
    {
        return false;
    }
    sched.clear();
    // Add your code below

    // Step 1 loop or two to initialize daily  schedule
    size_t num_days = avail.size(); // definitely columns
    cout << "num days" << num_days << endl;
    size_t num_workers = avail[0].size();
    cout << "num workers" << num_workers << endl; // definitely workers

    vector<size_t> numShiftsTracker;
    for (size_t t = 0; t < num_workers; t++)
    {
        numShiftsTracker.push_back(0);
    }

    cout << "shift tracker initialied" << endl;

    for (size_t day = 0; day < avail.size(); day++)
    {
        vector<Worker_T> hire;
        for (size_t hires = 0; hires < dailyNeed; hires++)
        {
            hire.push_back(INVALID_ID);
        }
        sched.push_back(hire);
    }

    cout << "avail initiated" << endl;
    int day = 0;
    int worker_num = 0;
    int shift_num = 0;
    AvailabilityMatrix avail_copy = avail;

    // Step 2 loop for backtracking
    bool truth;
    cout << "attempting to enter schedule helpet" << endl;

    const size_t dailyNeed_copy = dailyNeed;

    truth = schedule_helper(avail, dailyNeed_copy, maxShifts, numShiftsTracker, sched, day, worker_num, shift_num, 0);
    return truth;
}
