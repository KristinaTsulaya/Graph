#include <iostream>
#include <vector>
#include <queue>



class Graph {
private:
    struct Edge {
        int to;
    };
    std::vector<std::vector<Edge>> adj;
    size_t vertex_number;
    std::vector<std::vector<int>> matrix;
    size_t rows;
    size_t col;
    std::vector<bool> used;

    int get_vertex_number(int i, int j) {
        return i * col + j;
    }

    std::pair<int, int> get_pos(int vertex_num) {
        return {vertex_num / col, vertex_num % col};
    }

    bool check_pos(const std::pair<int, int>& position) {
        bool flag_1 = position.first >= 0 && position.first < rows;
        bool flag_2 = position.second >= 0 && position.second < col;
        return flag_1 && flag_2;
    }

    std::vector<std::pair<int, int>> get_nei(int i, int j) {
        std::vector<std::pair<int, int>> result;
        result.reserve(4);

        if (check_pos({i, j - 1})) {
            result.push_back({i,  j - 1});
        }
        if (check_pos({i - 1, j})) {
            result.push_back({i - 1,  j});
        }
        if (check_pos({i, j + 1})) {
            result.push_back({i,  j + 1});
        }
        if (check_pos({i + 1, j})) {
            result.push_back({i + 1, j});
        }

        return result;
    }

public:
    Graph(const std::vector<std::vector<int>>& matrix_) : matrix(std::move(matrix_)), rows(matrix.size()), col(matrix[0].size()),
                                                          vertex_number(matrix_.size() * matrix_[0].size()), used(vertex_number, false) {

        adj.resize(matrix.size() * matrix[0].size(), std::vector<Edge>());

        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[0].size(); ++j) {
                for (auto& [row_i, col_j] : get_nei(i, j)) {
                    if (matrix[row_i][col_j] == matrix[i][j]) {
                        adj[get_vertex_number(i, j)].push_back({get_vertex_number(row_i, col_j)});
                    }
                }
            }
        }
    }

    void solution(int start_i, int start_j, int value_to_change) {
        std::queue<int> queue;
        queue.push(get_vertex_number(start_i, start_j));

        while (!queue.empty()) {
            int tmp = queue.front();
            queue.pop();
            matrix[get_pos(tmp).first][get_pos(tmp).second] = value_to_change;
            used[tmp] = true;
            for (const auto& nei : get_nei(get_pos(tmp).first, get_pos(tmp).second)) {
                if (!used[get_vertex_number(nei.first, nei.second)]) {
                    queue.push(get_vertex_number(nei.first, nei.second));
                }
            }
        }

    }


};

int main() {
    std::vector<std::vector<int>> matrix;
    int rows, col;

    std::cin >> rows >> col;
    matrix.resize(rows, std::vector<int>());
    for (auto& row : matrix) {
        row.resize(col, 0);
    }
    for (auto& row : matrix) {
        for (auto& val : row) {
            std::cin >> val;
        }
    }

    std::pair<int, int> start_pos;
    std::cin >> start_pos.first >> start_pos.second;

    int value_to_change;
    std::cin >> value_to_change;

    Graph graph(matrix);

    graph.solution(start_pos.first, start_pos.second, value_to_change);

    return 0;
}
