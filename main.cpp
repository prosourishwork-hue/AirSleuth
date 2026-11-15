#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>
#include <cmath>
#include <memory>
#include <ctime>

using namespace std;

// ===========================================================================
// 1. UI & UTILITY
// ===========================================================================
namespace UI {
    const string RST = "\033[0m", BOLD = "\033[1m", RED = "\033[31m", 
                 GRN = "\033[32m", YEL = "\033[33m", BLU = "\033[34m", CYN = "\033[36m", GRY = "\033[90m";
    string pad(string s, size_t w) { return s.size() >= w ? s : s + string(w - s.size(), ' '); }
    string fmt(double v, int p = 2) { ostringstream o; o << fixed << setprecision(p) << v; return o.str(); }
    string pct(double v) { return fmt(v * 100, 1) + "%"; }
    string now() { time_t t = time(0); char b[100]; strftime(b, sizeof(b), "%Y-%m-%d %H:%M:%S", localtime(&t)); return string(b); }
}

// ===========================================================================
// 2. INHERITANCE & POLYMORPHISM (Suspects)
// ===========================================================================
class Suspect {
protected:
    string name; double lat, lon;
public:
    Suspect(string n, double la, double lo) : name(n), lat(la), lon(lo) {}
    virtual ~Suspect() = default;
    string getName() const { return name; }
    double getLat() const { return lat; }
    double getLon() const { return lon; }
    
    virtual string getType() const = 0;
    virtual string getRec() const = 0;
    virtual string getSDG() const = 0;
    virtual string getSeverity() const = 0;
    // NEW: Seasonal/Time profile
    virtual double activityFactor(int month, int hour) const = 0; 
};

class Industry : public Suspect {
public:
    Industry(string n, double la, double lo) : Suspect(n, la, lo) {}
    string getType() const override { return "Industry"; }
    string getRec() const override { return "Report to Pollution Control Board"; }
    string getSDG() const override { return "SDG 11.6"; }
    string getSeverity() const override { return "HIGH"; }
    double activityFactor(int m, int h) const override { return 1.0; } // Runs all year
};

class Stubble : public Suspect {
public:
    Stubble(string n, double la, double lo) : Suspect(n, la, lo) {}
    string getType() const override { return "Stubble"; }
    string getRec() const override { return "Advise avoiding outdoor activity"; }
    string getSDG() const override { return "SDG 13"; }
    string getSeverity() const override { return "HIGH"; }
    double activityFactor(int m, int h) const override { return (m == 10 || m == 11) ? 3.0 : 0.1; } // Peaks Oct-Nov
};

class Traffic : public Suspect {
public:
    Traffic(string n, double la, double lo) : Suspect(n, la, lo) {}
    string getType() const override { return "Traffic"; }
    string getRec() const override { return "Enforce odd-even / diversion"; }
    string getSDG() const override { return "SDG 11.2"; }
    string getSeverity() const override { return "MEDIUM"; }
    double activityFactor(int m, int h) const override { 
        return (h >= 8 && h <= 10) || (h >= 17 && h <= 20) ? 2.0 : 0.5; // Rush hours
    }
};

class Construction : public Suspect {
public:
    Construction(string n, double la, double lo) : Suspect(n, la, lo) {}
    string getType() const override { return "Construction"; }
    string getRec() const override { return "Order dust-suppression on site"; }
    string getSDG() const override { return "SDG 11.6"; }
    string getSeverity() const override { return "MEDIUM"; }
    double activityFactor(int m, int h) const override { return (h >= 9 && h <= 18) ? 1.5 : 0.0; } // Daytime
};

// ===========================================================================
// 3. STATION & WIND
// ===========================================================================
class Station {
    string name; double lat, lon;
public:
    Station(string n, double la, double lo) : name(n), lat(la), lon(lo) {}
    string getName() const { return name; }
    double getLat() const { return lat; }
    double getLon() const { return lon; }
};

class Wind {
    double dir;
public:
    Wind(double d) : dir(d) {}
    double getDir() const { return dir; }
};

// ===========================================================================
// 4. THE ANALYZER ENGINE
// ===========================================================================
class AirQualityAnalyzer {
private:
    vector<Station> stations;
    vector<shared_ptr<Suspect>> suspects;
    Wind wind;
    int month, hour;

    struct Result { shared_ptr<Suspect> susp; double score; };

    double calcScore(const Station& st, const shared_ptr<Suspect>& s) {
        double dist = sqrt(pow(s->getLat() - st.getLat(), 2) + pow(s->getLon() - st.getLon(), 2)) + 0.1;
        double angle = atan2(s->getLat() - st.getLat(), s->getLon() - st.getLon()) * 180.0 / M_PI;
        if (angle < 0) angle += 360;
        double diff = abs(wind.getDir() - angle); if (diff > 180) diff = 360 - diff;
        // Apply Seasonal/Time Profile here
        return ((1.0 - diff / 180.0) * 100.0 / dist) * s->activityFactor(month, hour);
    }

    vector<Result> getRanked(const Station& st, const Wind& w) {
        vector<Result> res;
        for (auto& s : suspects) res.push_back({s, calcScore(st, s)});
        sort(res.begin(), res.end(), [](Result a, Result b){ return a.score > b.score; });
        return res;
    }

public:
    AirQualityAnalyzer(vector<Station> st, vector<shared_ptr<Suspect>> susp, Wind w, int m, int h) 
        : stations(st), suspects(susp), wind(w), month(m), hour(h) {}

    // EXTRA 1 & 2: Compare Mode with Top-3 Share
    void runCompareMode() {
        cout << "\n" << UI::BOLD << UI::CYN << "=== COMPARE MODE: Top 3 Suspects (Month: " << month << ", Hour: " << hour << ") ===" << UI::RST << "\n";
        for (auto& st : stations) {
            auto ranks = getRanked(st, wind);
            double total = 0; for (auto& r : ranks) total += r.score;
            
            cout << UI::BOLD << st.getName() << UI::RST << ":\n";
            for (int i = 0; i < min((int)ranks.size(), 3); i++) {
                double share = total > 0 ? (ranks[i].score / total) * 100 : 0;
                cout << "  " << i+1 << ". " << UI::pad(ranks[i].susp->getName(), 15) 
                     << UI::pad(ranks[i].susp->getType(), 12) 
                     << "Score: " << UI::pad(UI::fmt(ranks[i].score), 6) 
                     << "Share: " << UI::pct(share/100) << "\n";
            }
        }
        cout << "\n";
    }

    // EXTRA 3: Action Priority List (Sorted by Severity)
    void printActionPriorityList() {
        struct ActionItem { string station, action, severity, sdg; double score; };
        vector<ActionItem> actions;
        
        for (auto& st : stations) {
            auto top = getRanked(st, wind)[0];
            actions.push_back({st.getName(), top.susp->getRec(), top.susp->getSeverity(), top.susp->getSDG(), top.score});
        }
        
        sort(actions.begin(), actions.end(), [](ActionItem a, ActionItem b) {
            if (a.severity != b.severity) return a.severity == "HIGH"; // High first
            return a.score > b.score; // Then by pollution score
        });

        cout << UI::BOLD << UI::CYN << "=== ACT FIRST PRIORITY LIST ===" << UI::RST << "\n";
        for (auto& a : actions) {
            string col = a.severity == "HIGH" ? UI::RED : UI::YEL;
            cout << col << "[" << UI::pad(a.severity, 6) << "]" << UI::RST 
                 << UI::pad(a.station, 15) << a.action << " (" << a.sdg << ")\n";
        }
        cout << "\n";
    }

    // EXTRA 4: Simple ASCII Map
    void printAsciiMap() {
        cout << UI::BOLD << UI::CYN << "=== ASCII MAP (S=Station, X=Suspect, ->=Wind) ===" << UI::RST << "\n";
        int gridSize = 15;
        vector<vector<char>> grid(gridSize, vector<char>(gridSize, '.'));
        
        // Helper to map lat/lon to grid (simplified box)
        auto mapCoord = [&](double lat, double lon) {
            int x = min(gridSize-1, max(0, (int)((lon - 77.0) * 30)));
            int y = min(gridSize-1, max(0, (int)((lat - 28.4) * 30)));
            return make_pair(x, y);
        };

        for (auto& s : suspects) { auto p = mapCoord(s->getLat(), s->getLon()); grid[p.second][p.first] = 'X'; }
        for (auto& st : stations) { auto p = mapCoord(st.getLat(), st.getLon()); grid[p.second][p.first] = 'S'; }

        for (int y = gridSize-1; y >= 0; y--) {
            for (int x = 0; x < gridSize; x++) cout << grid[y][x] << " ";
            if (y == gridSize/2) cout << "  <-- Wind (" << wind.getDir() << " deg)";
            cout << "\n";
        }
        cout << "\n";
    }

    // EXTRA 6: Log File
    void logRun(const string& filename) {
        ofstream f(filename, ios::app);
        if (!f.is_open()) return;
        f << "[" << UI::now() << "] RUN | Month: " << month << " Hour: " << hour 
          << " | Wind: " << wind.getDir() << " deg | Stations: " << stations.size() << "\n";
        for (auto& st : stations) {
            auto top = getRanked(st, wind)[0];
            f << "    - " << st.getName() << " -> Top: " << top.susp->getName() 
              << " (Score: " << UI::fmt(top.score) << ")\n";
        }
        f.close();
        cout << UI::GRN << "Logged run to " << filename << UI::RST << "\n";
    }
};

// ===========================================================================
// 5. MAIN DRIVER
// ===========================================================================
int main() {
    // Setup Data
    vector<Station> stations = {
        {"Anand Vihar", 28.65, 77.31}, {"ITO", 28.62, 77.24}, {"Punjabi Bagh", 28.67, 77.13}
    };
    Wind wind(270); // West wind
    
    vector<shared_ptr<Suspect>> suspects = {
        make_shared<Industry>("Factory A", 28.66, 77.30),
        make_shared<Stubble>("Farm B", 28.50, 77.10),
        make_shared<Traffic>("Traffic C", 28.63, 77.25),
        make_shared<Construction>("Site D", 28.68, 77.14)
    };

    // Run 1: October (Stubble Season), 9 AM (Morning Rush)
    AirQualityAnalyzer morningAnalyzer(stations, suspects, wind, 10, 9);
    morningAnalyzer.runCompareMode();
    morningAnalyzer.printActionPriorityList();
    morningAnalyzer.printAsciiMap();
    morningAnalyzer.logRun("history.log");

    // Run 2: July (Monsoon), 3 PM (Afternoon)
    cout << "\n--------------------------------------------------\n";
    AirQualityAnalyzer afternoonAnalyzer(stations, suspects, wind, 7, 15);
    afternoonAnalyzer.runCompareMode(); // You will see Stubble has almost 0 score here!
    afternoonAnalyzer.printActionPriorityList();

    return 0;
}