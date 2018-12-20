#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>


using namespace std;


class DataPoint {
	private:
		double x, y;
	public:
		DataPoint() {
			clear();
		}
		DataPoint(double x, double y) {
			this->x = x;
			this->y = y;
		}

		double getX() {
			return x;
		}

		double getY() {
			return y;
		}

		double dist(const DataPoint &other) {
			return (this->x - other.x) * (this->x - other.x) +
						 (this->y - other.y) * (this->y - other.y);
		}
		void add(const DataPoint &other) {
			this->x += other.x;
			this->y += other.y;
		}
		void copy(const DataPoint &other) {
			this->x = other.x;
			this->y = other.y;
		}
		void clear() {
			this->x = this->y = 0;
		}
		void average_by(double n) {
			this->x /= n;
			this->y /= n;
		}

		bool equals (const DataPoint &other) {
			static double EPS = 0.0001;
			return abs(this->x - other.x) <= EPS &&
					   abs(this->y - other.y) <= EPS;
		}
};

class KMeans {

private:
	std::vector <DataPoint> data;
	std::vector <DataPoint> clusters;
	std::vector <DataPoint> sum;
	std::vector <int> count;
	std::vector<string> colors = {
		"red", "green", "black", "yellow", "gray", "blue"
	};
	int get_closest_cluster_index (const DataPoint &dp) {
		int closest_ind = 0;
		for (int ind = 0 ; ind < (int) clusters.size() ; ind ++) {
			if (clusters[ind].dist(dp) < clusters[closest_ind].dist(dp)) {
				closest_ind = ind;
			}
		}
		return closest_ind;
	}
public:
	void run_kmeans() {
		cout << "run_kmeans\n";


		bool changed = false;
		int cntr = 0;

		do {
				changed = false;
				for (DataPoint &dp : sum) {
					dp.clear();
				}
				for (int &dp : count) {
					dp = 0;
				}
				for (DataPoint &dp : data) {
					int cluster_ind = get_closest_cluster_index(dp);
					sum[cluster_ind].add(dp);
					count[cluster_ind] ++;
				}

				for (int i = 0 ; i < (int) sum.size() ; ++i) {
					if (count[i] == 0) continue;
					sum[i].average_by(count[i]);
					if (sum[i].equals(clusters[i]))
						continue;
					changed = true;
					clusters[i].copy(sum[i]);
				}
				cntr ++;
		} while (changed == true);
	}

	void get_data(const std::vector<DataPoint> &data, int num_clusters) {
		cout << "get_data\n";
		cout << "num_clusters = " << num_clusters << "\n";

		for (int i = 0 ; i < num_clusters ; ++i) {
			this->clusters.push_back(data[rand() % num_clusters]);
		}
		this->sum.resize(num_clusters);
		this->count.resize(num_clusters);

		for (DataPoint dp : data) {
			// cout << dp.getX() << " " << dp.getY() << "\n";
		}
		this->data = data;
	}

	void output(string &file_name) {
		cout << "output\n";

		ofstream out(file_name.c_str());
		// out<< this->data.size() << " " << this->clusters.size();

		for (DataPoint &dp : data) {
			// cout << dp.getX() << " " << dp.getY() << "\n";
			int cluster_ind = get_closest_cluster_index(dp);
			out << int(dp.getX()) << " " << int(dp.getY()) << " " << colors[cluster_ind] << "\n";
		}
	}

	static void input(string &file_name, std::vector<DataPoint> &res, int &num_clusters) {
		ifstream in(file_name);
		string line;

		res.clear();
		num_clusters = 0;

		int input_size = 0;

		in >> input_size >> num_clusters;

		for (int i = 0 ; i < input_size ; ++i) {
			double x, y;
			in >> x >> y;
			DataPoint p(x, y);
			res.push_back(p);
		}
	}

};




int main() {
	srand(time(NULL));
	std::vector<DataPoint> v;
	int k;
	string file = "my_data10.txt";
	string file_out = "my_output10.txt";


	KMeans obj;
	obj.input (file, v, k);
	obj.get_data(v, k);
	obj.run_kmeans();
	obj.output(file_out);


}
