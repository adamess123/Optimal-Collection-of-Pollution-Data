#include <bits/stdc++.h>
#include <cmath>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
class Sensor {
public:
  int x;
  int y;
  int r;
  int wt;
  int ct;
  Sensor() {
    x = 0;
    y = 0;
    r = 0;
    wt = 0;
    ct = 0;
  }
  Sensor(int x, int y, int r, int wt, int ct) {
    this->x = x;
    this->y = y;
    this->r = r;
    this->wt = wt;
    this->ct = ct;
  }
  int is_near(Sensor &S) {
    if (sqrt(pow((x - S.x), 2) + pow((y - S.y), 2)) > r) { // distance formula
      return 0;
    } else
      return 1;
  }
};
void set_weights(vector<Sensor> &sensors) {
  int i = 0;
  int j = 0;
  for (i = 0; i < sensors.size(); i++) {
    for (j = 0; j < sensors.size(); j++) {
      if (i == j) {
        continue;
      }
      sensors[i].wt += sensors[i].is_near(sensors[j]);
    }
  }
}
vector<Sensor> search(int &W, vector<Sensor> S, int L) {
  int C = 0;
  vector<Sensor> U, G;
  priority_queue<pair<int, int>> pq;
  // calculate ratio and store in priority queue
  for (int i = 0; i < S.size(); i++) {
    int ratio = S[i].wt / S[i].ct; // calculates ratio of W and C
    pair<int, int> p = make_pair(ratio, i);
    pq.push(p);
    while (!pq.empty()) {

      U.push_back(S[pq.top().second]); // sorts U by ratio of W and C
      pq.pop();
    }
  }

  while (C < L && !U.empty()) {
    if (C + (U[0].ct) <= L) {
      G.push_back(U[0]);
      C = C + U[0].ct;
    }
    U.erase(U.begin()); // erases beginning element of U
  }
  int weight = 0;
  for (int i = 0; i < G.size(); i++) {
    weight += G[i].wt;
  }
  if (weight > W) {
    W = weight;
    return G;
  }
  return S;
}

vector<pair<pair<int, int>, pair<int, int>>> uniformDistro() {
  srand(time(NULL)); // random generation
  int x, y;
  vector<pair<int, int>> coords,
      weightCost; // pairs to store x,y and weight,cost respectively
  vector<pair<pair<int, int>, pair<int, int>>>
      sensorData; // stores the coords and weight/Cost in one place

  for (int i = 0; i < 50; i++) {
    x = rand() % 101; // random x from 0-100
    y = rand() % 101; // random y from 0-100

    int cWeight = 0;         // generates a weight value from 0-50
    int cCost = rand() % 11; // generates a weight value from 0-10

    coords.push_back(make_pair(x, y)); // assigns x and y to coords
    weightCost.push_back(
        make_pair(cWeight, cCost)); // assigns weight and cost to weightCost
    sensorData.push_back(make_pair(
        coords[i],
        weightCost[i])); // pushes coords and weightCost values to sensorData
  }
  return sensorData;
}
void clusterHelper(int x_center, int y_center, int cost, int numToAdd,
                   vector<Sensor> &sensors) { // made to generate random
                                              // clusters around a center
  for (int i = 0; i < numToAdd; i++) {
    int cWeight = 1;
    int x_shift = rand() % 21 - 10; // value -10 to 10
    int y_shift = rand() % 21 - 10; // value -10 to 10
    int x_new = x_center + x_shift;
    int y_new = y_center + y_shift;
    int cCost = cost + rand() % 3 - 1;
    sensors.push_back(Sensor(x_new, y_new, 5, cWeight, cCost));
  }
}
vector<Sensor> clusterDistro() {
  vector<Sensor> sensors; // pairs to store x,y and weight,cost respectively
  int i = 0;
  while (i < 4) {
    bool to_add = true;
    int x_new = rand() % 71 + 15; // random value between 15-85
    int y_new = rand() % 71 + 15;
    for (int j = 0; j < sensors.size();
         j++) { // to ensure origin is not within 15 unit radius of others
      if (sqrt(pow((sensors[i].x - x_new), 2) +
               pow((sensors[i].y - y_new), 2)) <= 15) { // distance formula
        to_add = false;
        break;
      }
    }
    if (to_add) {
      int cWeight = 1;
      int cCost = rand() % 5 + 2; // x_new / 10;
      sensors.push_back(Sensor(x_new, y_new, 5, cWeight, cCost));
      i++;
    }
  }
  for (i = 0; i < 4; i++) {
    clusterHelper(sensors[i].x, sensors[i].y, sensors[i].ct, 24, sensors);
  }
  set_weights(sensors);
  return sensors;
}
template <class BidiIter>
BidiIter random_unique(
    BidiIter begin, BidiIter end,
    size_t num_random) { // imported unique random value to avoid repeats
  size_t left = std::distance(begin, end);
  while (num_random--) {
    BidiIter r = begin;
    std::advance(r, rand() % left);
    std::swap(*begin, *r);
    ++begin;
    --left;
  }
  return begin;
}
vector<Sensor> randomGen(vector<Sensor> &S, int L, int &W) {
  vector<bool> visited(S.size(), false);
  vector<Sensor> G;
  int count = 0;
  int C = 0;
  int numTries = 0;
  while (C < L && numTries <= 10) {
    numTries++;
    int idx = rand() % S.size(); // produces a random index each iteration
    if (visited[idx] == true) {
      continue;
    }
    count++;
    visited[idx] = true;
    if (C + (S[idx].ct) <=
        L) { // if cost is less than budget, update values and continue going
      numTries = 0;
      G.push_back(S[idx]);
      C += S[idx].ct;
      W += S[idx].wt;
    }
  }
  return G;
}
vector<Sensor> randomApproach(vector<Sensor> X, int L) {
  int W = 0;
  vector<Sensor> result = randomGen(X, L, W);
  return result;
  /*cout << "Our budget is: " << L << endl;
  cout << "We havector<Sensor> X = clusterDistro();
  cout << "Optimal solution: " << endl;
  optimalApproach(X, L, numIters, subsetSize);

  cout << "Pure greedy solution: " << endl;
  pureGreedy(X, L);

  cout << "Random solution: " << endl;
  randomApproach(X, L);ve purchased " << result.size() << " random sensors" <<
  endl; cout << "Total weight is: " << W << endl; cout << "\n"; for (int i = 0;
  i < result.size(); i++) { cout << "X coordinate: " << result[i].x << endl;
    cout << "Y coordinate: " << result[i].y << endl;
    cout << "Weight: " << result[i].wt << endl;
    cout << "Cost: " << result[i].ct << endl;
    cout << "\n";
  }*/
}
vector<Sensor> pureGreedy(vector<Sensor> X, int L) {
  int W = 0;
  vector<Sensor> result = search(W, X, L);
  return result;
  /*cout << "Our budget is: " << L << endl;
  cout << "We have purchased " << result.size() << " greedy sensors" << endl;
  cout << "Total weight is: " << W << endl;
  cout << "\n";
  for (int i = 0; i < result.size(); i++) {
    cout << "X coordinate: " << result[i].x << endl;
    cout << "Y coordinate: " << result[i].y << endl;
    cout << "Weight: " << result[i].wt << endl;
    cout << "Cost: " << result[i].ct << endl;
    cout << "\n";
  }*/
}
vector<Sensor> optimalApproach(vector<Sensor> X, int L, int numIters,
                               int subsetSize) {
  int W = 0;
  int temp_W = 0;
  vector<Sensor> sub, temp, res;
  // cout << X[0].x;
  for (int i = 0; i < numIters; i++) {
    random_unique(X.begin(), X.end(), subsetSize);
    for (int j = 0; j < subsetSize; j++) {
      sub.push_back(X[j]);
      // cout << X[j].y << endl;
    }
    // cout << sub.size() << endl;
    temp = search(W, sub, L);
    if (temp_W != W) {
      res = temp;
    }
    temp_W = W;
    sub.clear();
  }
  return res;
  /*cout << "Our budget is: " << L << endl;
  cout << "Our sample size is: " << subsetSize << endl;
  cout << "We have purchased " << res.size() << " viable sensors" << endl;
  cout << "Total weight is: " << W << endl;
  cout << "\n";
  for (int i = 0; i < res.size(); i++) {
    cout << "X coordinate: " << res[i].x << endl;
    cout << "Y coordinate: " << res[i].y << endl;
    cout << "Weight: " << res[i].wt << endl;
    cout << "Cost: " << res[i].ct << endl;
    cout << "\n";
  }*/
}
int compute_weight(vector<Sensor> sensors) {
  int weights = 0;
  for (Sensor s : sensors) {
    weights += s.wt;
  }
  //cout << weights;
  return weights;
}

int main() {
  srand(time(NULL));      // random generation
  int L = 52;
  int n = 100000;
  int numIters = 50;
  size_t subsetSize = 30;
  double average_p = 0;
  double average_q = 0;
  for (int i = 0; i < n; i++) {
    vector<Sensor> X = clusterDistro();
    // cout << "Optimal solution: " << endl;
    vector<Sensor> O = optimalApproach(X, L, numIters, subsetSize);

    // cout << "Pure greedy solution: " << endl;
    vector<Sensor> G = pureGreedy(X, L);

    // cout << "Random solution: " << endl;
    vector<Sensor> R = randomApproach(X, L);
    int G_weight = compute_weight(G);
    int O_weight = compute_weight(O);
    int R_weight = compute_weight(R);
    average_p += (O_weight - R_weight) / double(R_weight);
    average_q += (O_weight - G_weight) / double(G_weight);
  }
  average_p /= n;
  average_p *= 100;
  average_q /= n;
  average_q *= 100;
  cout << "Average percent improvement by using optimal over random is "
       << average_p << "%" << endl;
  cout << "Average percent improvement by using optimal over greedy is "
       << average_q << "%" << endl;

  return 0;
}