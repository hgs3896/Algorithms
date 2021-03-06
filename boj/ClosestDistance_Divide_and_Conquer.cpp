#include <stdio.h>
#include <climits>
#include <utility>
#include <vector>
#include <algorithm>

// Aliasing
using Point = std::pair<int,int>;
using Points = std::vector<Point>;

// Define Y axis sort
auto cmp = [](const Point& lhs, const Point& rhs) {
	if (lhs.second == rhs.second) return lhs.first < rhs.first;
	else return lhs.second < rhs.second;
};

// Function Prototypes
inline int dist(const Point& p1, const Point& p2);
int minDist(const Points& p, int L, int R);

int main() {
	int n;
	Points vertex;

	// Get Input
	scanf("%d", &n);	
	vertex.resize(n);
	
	for (auto i = 0; i < n; ++i) {
		scanf("%d %d", &vertex[i].first, &vertex[i].second);
	}

	// Preprocess
	std::sort(vertex.begin(), vertex.end());
	
	// Process & Print
	auto result = minDist(vertex, 0, vertex.size() - 1);

	printf("%d\n", result);
}

int minDist(const Points& p, int L, int R) {
	// Exception Handling
	if (L < 0 || R > p.size()){
		throw - 1;
	}
	// Base Condition
	if (L >= R) {
		return INT_MAX/2;
	}else {
		// Recursive Definition
		auto m = (L + R) / 2;
		auto Lmin = minDist(p, L, m);
		auto Rmin = minDist(p, m+1, R);
		auto d = std::min(Lmin, Rmin);
		
		// Find band
		Points rBand;

		for (auto j = m + 1; j <= R && (p[j].first - p[m].first) < d; ++j) {
			rBand.push_back(p[j]);
		}

		// Sort by Y axis
		std::sort(rBand.begin(), rBand.end(), cmp);

		for (auto i = m; i >= L && (p[m].first - p[i].first) < d; --i) {
			auto lower = std::lower_bound(rBand.begin(), rBand.end(), Point(p[i].first, p[i].second - d), cmp);
			auto upper = std::upper_bound(rBand.begin(), rBand.end(), Point(p[i].first, p[i].second + d), cmp);
			for (auto j = lower; j < upper; ++j) {
				d = std::min(d, dist(p[i], *j));
			}
		}

		return d;
	}
}

int dist(const Point& p1, const Point& p2) {
	return (p1.first - p2.first)*(p1.first - p2.first) + (p1.second - p2.second)*(p1.second - p2.second);
}