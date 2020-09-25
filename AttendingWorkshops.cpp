#include<bits/stdc++.h>
#include <vector>
#include <set>

using namespace std;

struct Workshop {
    int start_time, duration, end_time;
};

struct Available_Workshops { 
    int n;
    vector<Workshop> workshop_list;
};


Available_Workshops* initialize (int start_time[], int duration[], int n) {
    int end_time;
    Available_Workshops* A = new Available_Workshops();

    A->n = n;

    for (int i = 0; i < n; ++i) {
        end_time = start_time[i] + duration[i];
        A->workshop_list.push_back(Workshop{start_time[i], duration[i], end_time});
    }
    return A;
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
    Workshop* attendable_workshop;
    set<Workshop*> attending, candidates;
    set<Workshop*>::iterator it;
    int earliest_end, num_candidates;

    for (int i = 0; i < ptr->n; ++i){
        candidates.insert(&ptr->workshop_list[i]);
    }

    num_candidates = candidates.size();

    while (num_candidates > 0)
    {
        // Initialise earliest ending workshop to first candidate
        attendable_workshop = *candidates.begin();
        earliest_end = attendable_workshop->end_time;
        
        // Find minimum end
        for(Workshop* workshop : candidates) {
            if (workshop->end_time < earliest_end) {
                attendable_workshop = workshop;
                earliest_end = attendable_workshop->end_time;
            }
        }

        // Add earliest end to attending set
        attending.insert(attendable_workshop);
        candidates.erase(attendable_workshop);
        --num_candidates;

        if (num_candidates == 0)
            break;

        // Eliminate intersecting workshops from candidate set
        for(int i = 0; i < num_candidates; ++i) {
            it = candidates.begin();
            advance(it, i);
            Workshop* workshop = *it;

            if (workshop->start_time < attendable_workshop->end_time && 
                attendable_workshop->start_time < workshop->end_time) {
                
                    candidates.erase(it);
                    --num_candidates;
                    --i;
            }
        }
    }

    return attending.size();
}

// Hackerrank testing template
int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}