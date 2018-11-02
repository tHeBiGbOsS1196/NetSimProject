#include "network.h"
#include "random.h"
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>

RandomNumbers r;

void Network::resize(const size_t& s) {
	values.clear();
	values.resize(s);
	r.normal(values, 0, 1);
}

bool Network::add_link(const size_t& a, const size_t& b) {
	if (values.size() <= std::max(a,b) or a == b) return false;
	for (auto x : neighbors(a)) if(x == b) return false;
	links.emplace(a,b);
	links.emplace(b,a);
	return true;
}

size_t Network::random_connect(const double& n) {
	links.clear();
	size_t sum(0);
	for (size_t j(0) ; j < values.size() ; ++j) {	
		std::vector <int> node(20*n);
		r.uniform_int(node, 0, values.size() - 1 );
		int dist(r.poisson(n));
		for (int i(0) ; i < dist ; i++) {	
			size_t k(0);
			try {	
			do {
				if(i + k == node.size() - 1 and degree(j) <= values.size())
				{
					k = 0;
					r.uniform_int(node, 0, values.size() - 1);
				}
				else if(degree(j) >= values.size() - 1) {
					throw std::string ("Un noeud est déjà lié à tous les autres noeuds");
				}
				else {
				add_link(j, node[i + k]);
				++k;
				}
			}while(!(add_link(j, node[i + k]) and k + i < node.size()));
			++sum;	
			    }catch(std::string &e){ std::cerr << e << std::endl; }    				
		}	
	}
	return sum;
}

size_t Network::set_values(const std::vector<double>& node) {	                   
	if (values.size() >= node.size()) {   
		values.erase(values.begin(), values.begin() + node.size());
		values.insert(values.begin(), node.begin(), node.end());
		return node.size();
	}
	values.clear();
	values.insert(values.begin(), node.begin(), node.begin() + values.size());
	return values.size();
}

size_t Network::size() const { return values.size(); }
size_t Network::degree(const size_t &_n) const { return links.count(_n); }
double Network::value(const size_t &_n) const { return values[_n]; }

std::vector<double> Network::sorted_values() const {
	std::vector<double> a(values);
	std::sort(a.begin(), a.end(), std::greater<double>());
	return a;
}

std::vector<size_t> Network::neighbors(const size_t& point) const {
	std::vector<size_t> neig;
	for (auto& x : links)
		if(x.first == point) neig.push_back(x.second);
	return neig;
}
