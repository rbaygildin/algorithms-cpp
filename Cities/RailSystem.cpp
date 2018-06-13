/*
 * Студента: Ярных Роман Вячеславович
 * Группа: БПИ 141
 * Подгруппа: 2
 * Дата: 01.06.2016
 * Проект: EuropeByRail
 * Язык: C++ 11
 * Компилятор: GCC
 * Среда: CLion
 */

#pragma warning (disable:4786)
#pragma warning (disable:4503)

#include <unordered_set>
#include "RailSystem.h"

typedef map<string, City*>::iterator CITY_IT;
typedef list<Service*>::iterator SERVICE_IT;

/*
 * Reset data information of rail system
 */
void RailSystem::reset(void) {

	for(map<string, City*>::iterator city_it = cities.begin(); city_it != cities.end(); city_it++){
		City *city_ = city_it->second;
		city_->total_distance = 0;
		city_->visited = false;
		city_->total_fee = 0;
	}
}

/*
 * Allocate instance for rail system and load data into it from file
 */
RailSystem::RailSystem(string const &filename) {

    load_services(filename);
}

/*
 * Load data of rail system from file
 */
void RailSystem::load_services(string const &filename) {

	ifstream inf(filename.c_str());
	string from, to;
	int fee, distance;

	while ( inf.good() ) {

		// Read in the from city, to city, the fee, and distance.
		inf >> from >> to >> fee >> distance;

		if ( inf.good() ) {
			if(outgoing_services.find(from) == outgoing_services.end())
				outgoing_services[from] = list<Service*>();
			outgoing_services[from].push_back(new Service(to, fee, distance));
			if(cities.find(from) == cities.end())
				cities[from] = new City(from);
		}
	}

	inf.close();
}

/*
 * Deallocate instance
 */
RailSystem::~RailSystem(void) {
	for(map<string, City*>::iterator city_it = cities.begin(); city_it != cities.end(); city_it++){
		delete city_it->second;
	}
	cities.clear();
	for(map<string, list<Service*>>::iterator from_it = outgoing_services.end(); from_it != outgoing_services.end(); from_it++){
		for(list<Service*>::iterator service_ = from_it->second.begin(); service_ != from_it->second.end(); service_++){
			delete *service_;
		}
	}
	outgoing_services.clear();
}

/*
 * Print out cheapest path route from one city to another
 */
void RailSystem::output_cheapest_route(const string& from,
                const string& to, ostream& out) {

	reset();
	pair<int, int> totals = calc_route(from, to);

	if (totals.first == INT_MAX) {
		out << "There is no route from " << from << " to " << to << "\n";
	} else {
		out << "The cheapest route from " << from << " to " << to << "\n";
		out << "costs " << totals.first << " euros and spans " << totals.second
			<< " kilometers\n";
        cout << recover_route(to) << "\n\n";
	}
}

/*
 * Check if city exists
 */
bool RailSystem::is_valid_city(const string& name) {

	return cities.count(name) == 1;
}

/*
 * Calculate cheapest route by mean of Dijkstra's algorithm
 */
pair<int, int> RailSystem::calc_route(string from, string to) {
    // You can use another container
	priority_queue<City*, vector<City*>, Cheapest> candidates;
	unordered_set<string> marked_;

	for(CITY_IT city_it = cities.begin(); city_it != cities.end(); city_it++){
		city_it->second->total_fee = INT_MAX;
		city_it->second->total_distance = 0;
	}

	cities[from]->total_fee = 0;
	candidates.push(cities[from]);

	while(!candidates.empty()){
		City* current_city_ = candidates.top();
		candidates.pop();
		if(marked_.find(current_city_->name) != marked_.end())
			continue;
		marked_.insert(current_city_->name);
		list<Service*> services_ = outgoing_services[current_city_->name];
		for(SERVICE_IT service_it = services_.begin(); service_it != services_.end(); service_it++){
			Service* service_ = *service_it;
			City* to_ = cities[service_->destination];
			if(to_->total_fee > (service_->fee + current_city_->total_fee)){
				to_->total_fee = service_->fee + current_city_->total_fee;
				to_->total_distance = service_->distance + current_city_->total_distance;
				to_->visited = true;
				to_->from_city = current_city_->name;
				candidates.push(to_);
			}
		}
	}


    if (cities[to]->visited) {
            return pair<int,int>(cities[to]->total_fee, cities[to]->total_distance);
    } else {
            return pair<int,int>(INT_MAX, INT_MAX);
    }

}

/*
 * Recover route
 */
string RailSystem::recover_route(const string& city) {
	string path_ = city;
    string from_ = cities[city]->from_city;
	while(from_ != ""){
		path_ = from_ + " to " + path_;
		from_ = cities[from_]->from_city;
	}
	return path_;
}

/*
 * Get cheapest route
 */
Route RailSystem::getCheapestRoute(const string& from, const string& to){
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p =  calc_route(from,to);
    return Route(from,to,p.first,p.second);
}