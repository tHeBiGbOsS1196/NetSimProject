#include "network.h"
#include "random.h"
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>

RandomNumbers r;

void Network::resize(const size_t& s)
{
	values.clear();
	values.resize(s);
	r.normal(values, 0, 1);
}

bool Network::add_link(const size_t& a, const size_t& b)
{
	if (values.size() < (a - 1) or values.size() < (b - 1) or a == b)
	return false;
	for (auto x : neighbors(a))
	{
		if(x == b)
		return false;
	}
	links.emplace(a,b); // links.insert(std::pair<size_t,size_t>(a,b));
	links.emplace(b,a);
	return true;
}

size_t Network::random_connect(const double& n)
{
	links.clear();
	size_t sum(0);
	for (auto x : values)
	{	
		std::vector <int> node;
		node.resize(5*n);
		r.uniform_int(node, 0, values.size() - 1);
		//for (auto x : node) {std::cout << x << " "; }
		//std::cout << std::endl;
		int dist(r.poisson(n));
		//if (dist > 2*n) {dist = 2*n;}
		for (int i(0); i < dist; i++)
		{
			//std::cout << dist;
			//if(add_link(x, node[i])) {++sum;}
			++sum;
			add_link(x, node[i]);					
		}	
		//std::cout << std::endl;
	}
	//for (auto x : values) {sum += degree(x);}
	return sum;
}

size_t Network::set_values(const std::vector<double>& node)
{
	/*if (values.size() != node.size())throw std::string                      
	("Erreur : Tentative de reset avec un nombre éronné de valeurs.");*/
	values.clear();
	for (auto x : node)
	values.push_back(x);
	return values.size();
}

size_t Network::size() const
{
	return values.size();
}

size_t Network::degree(const size_t &_n) const
{
	/*if (links.size() < (_n - 1))throw std::string                      
	("Erreur : Demande de degré d'élement non existant.");*/
	return links.count(_n);
}

double Network::value(const size_t &_n) const
{
	/*if (values.size() < (_n - 1))throw std::string                      
	("Erreur : Demande de valeur d'élement non existant.");*/
	return values[_n];
}

std::vector<double> Network::sorted_values() const
{
	if(values.empty()) throw std::string                      
	("Erreur : Demande réaranger un tableau vide.");
	std::vector<double> a(values);
	std::sort(a.begin(), a.end(), std::greater<double>());
	return a;
}

std::vector<size_t> Network::neighbors(const size_t& point) const
{
	/*if (links.size() < (point - 1))throw std::string                      
	("Erreur : Demande de voisin d'élement non existant.");*/
	std::vector<size_t> neig;
	for (auto& x : links)
	{
		if(x.first == point) neig.push_back(x.second);
	}
	return neig;
}
