#include <string>
#include <vector>
#include <algorithm>

class Solution {
private:
    // Helper function to convert "MM-DD" to a day number from 1 to 365
    int dateToDayOfYear(std::string date) {
        std::vector<int> daysPerMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // Extract month and day from the "MM-DD" format
        int month = std::stoi(date.substr(0, 2));
        int day = std::stoi(date.substr(3, 2));
        
        int dayOfYear = day;
        for (int i = 0; i < month - 1; ++i) {
            dayOfYear += daysPerMonth[i];
        }
        
        return dayOfYear;
    }

public:
    int countDaysTogether(std::string arriveAlice, std::string leaveAlice, std::string arriveBob, std::string leaveBob) {
        // Convert all dates to day numbers
        int startA = dateToDayOfYear(arriveAlice);
        int endA = dateToDayOfYear(leaveAlice);
        int startB = dateToDayOfYear(arriveBob);
        int endB = dateToDayOfYear(leaveBob);
        
        // Find the intersection of the two intervals
        int startOverlap = std::max(startA, startB);
        int endOverlap = std::min(endA, endB);
        
        // Calculate overlapping days (return 0 if there is no overlap)
        return std::max(0, endOverlap - startOverlap + 1);
    }
};
