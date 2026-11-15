AirSleuth: Delhi Pollution Source Detective

AirSleuth is an object-oriented C++ console application that traces the most likely source of air pollution (industry, stubble burning, traffic, construction) at Delhi's monitoring stations, using wind direction, distance, and seasonal and time-of-day activity patterns.

Problem Statement

Delhi's monitoring stations report how bad the air is (AQI) but not where the pollution comes from, which delays targeted action against its sources. This project builds an object-oriented C++ system that identifies the most probable pollution source for each station using wind direction, distance and seasonal activity patterns, and recommends corrective action.

Features
Suspect ranking: scores every pollution source for each station based on distance, wind alignment and source activity.
Compare mode: shows the top 3 suspects per station with each one's percentage share of the total score.
Seasonal and time-of-day profiles: each source type has its own activity pattern (for example, stubble burning peaks in Oct-Nov, traffic peaks at rush hours, construction runs in the daytime).
Recommended actions: every source type maps to a suggested action, a severity level and an SDG target.
Action priority list: an "act first" list sorted by severity and pollution score.
ASCII map: a simple console map of stations (S), suspects (X) and wind direction.
CSV report export: saves results to report.csv.
Run log: appends each run, with a timestamp, to history.log.
OOP Concepts Used
Concept	Where it is used
Abstraction	Suspect is an abstract base class with pure virtual functions (getType, getRec, getSDG, getSeverity, activityFactor)
Inheritance	Industry, Stubble, Traffic and Construction derive from Suspect
Polymorphism	Recommendations, severity and activity patterns are resolved at runtime through shared_ptr<Suspect>
Encapsulation	Station, Wind and Suspect keep their data private or protected and expose getters
Composition	AirQualityAnalyzer owns the stations, suspects and wind
Virtual destructor	Suspect has a virtual destructor for safe deletion through base pointers
Smart pointers	std::shared_ptr manages the suspect objects
How to Compile and Run

Requirements: a C++17 compiler (g++ / MinGW).

bash
# clone the repository
git clone https://github.com/prosourishwork-hue/AirSleuth.git
cd AirSleuth

# compile
g++ -std=c++17 -Iinclude src/main.cpp -o airsleuth

# run (Linux / macOS)
./airsleuth

# run (Windows)
airsleuth.exe
Project Structure
AirSleuth/
├── include/        header files (geometry.h, suspect.h, wind.h)
├── src/            main.cpp and generated output files
├── data/           data files
├── tests/          tests
└── README.md
Data Files
File	Purpose
src/report.csv	Output report: top suspect, type, score, recommended action and SDG for each station
src/history.log	Output log: timestamped record of every run (generated at runtime, not tracked by Git)
data/	Folder for input datasets (stations and suspects)
SDG Mapped
SDG 11: Sustainable Cities and Communities (Target 11.6: reduce the adverse environmental impact of cities, including air quality). Identifies pollution sources in Delhi so authorities can act on them.
SDG 3: Good Health and Well-being (Target 3.9: reduce illness from air pollution). Faster source identification means less exposure to harmful air.
SDG 13: Climate Action. Tracing sources like stubble burning and industrial emissions helps with curbing them.
Future Scope
Real-time data from CPCB or OpenAQ
GIS map visualization
Machine learning for source prediction
