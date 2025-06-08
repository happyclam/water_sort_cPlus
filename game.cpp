// game.cpp
#include "node.h"
#include <queue>
#include <chrono>
#include <iostream>

Box bfs(Node& node) {
    Box result;
    std::queue<Box> queue;
    queue.push(node.getValue());
    int cnt = 0;

    while (!queue.empty()) {
        Box box = queue.front();
        queue.pop();
        for (size_t i = 0; i < box.getBottles().size(); ++i) {
            bool emptyBottleFlg = false;
            for (size_t j = 0; j < box.getBottles().size(); ++j) {
                if (j == i) continue;
                if (box.getBottles()[j].size() >= MAX_UNIT) continue;
                if (box.getBottles()[i].size() <= 0) continue;
                if (box.getBottles()[i].check()) continue;
                if (emptyBottleFlg) continue;
                if (box.getBottles()[j].empty()) {
                    emptyBottleFlg = true;
                }
                if (box.getBottles()[i].monoCheck() && box.getBottles()[j].empty()) continue;
                if (!(box.getBottles()[j].empty() || box.getBottles()[i].back() == box.getBottles()[j].back())) continue;
                cnt++;
                Box temp = box.deepCopy();
/* 
                std::cout << "DEBUG: Before pour, temp.bottles[i].size() = " << temp.getBottles()[i].size()
                          << ", temp.bottles[j].size() = " << temp.getBottles()[j].size() << std::endl;
 */
                temp.getBottles()[i].pour(temp.getBottles()[j]);
/* 
                std::cout << "DEBUG: After pour, temp.bottles[i].size() = " << temp.getBottles()[i].size()
                          << ", temp.bottles[j].size() = " << temp.getBottles()[j].size() << std::endl;
                std::cout << "DEBUG: temp state after pour: ";
                for (const auto& b : temp.getBottles()) {
                    std::cout << "[";
                    for (size_t k = 0; k < b.size(); ++k) {
                        std::cout << b[k] << (k < b.size() - 1 ? "," : "");
                    }
                    std::cout << "]";
                }
                std::cout << ", check() = " << temp.check() << std::endl;
                std::cout << ", cnt = " << cnt << std::endl;
 */                
                std::string md5hash = Node::makeHash(temp.getBottles());

                if (Node::checkDup(md5hash)) {
                    continue;
                } else {
                    Node::setDup(md5hash);
                }

                Node newNode(temp);
                bool ret = node.add(newNode, box);
                if (!ret) {
                    std::cout << "Error" << std::endl;
                    std::cout << "cnt = " << cnt << std::endl;
                    std::cout << "temp = ";
                    for (const auto& b : temp.getBottles()) {
                        std::cout << "[";
                        for (size_t k = 0; k < b.size(); ++k) {
                            std::cout << b[k] << (k < b.size() - 1 ? "," : "");
                        }
                        std::cout << "]";
                    }
                    std::cout << std::endl;
                    exit(1);
                }
                if (temp.check()) {
                    std::cout << "cnt = " << cnt << std::endl;
                    std::cout << "Complete!!" << std::endl;
                    result = temp;
                    return result;
                }

                queue.push(temp);
            }
            if (!result.getBottles().empty()) break;
        }
        if (!result.getBottles().empty()) break;
    }

    return result;
}
Box dfs(Node& node, Box box, int depth) {
    Box result; // デフォルト構築（空）
    static int cnt = 0; // 試行回数を追跡（デバッグ用、BFSのcnt=497参考）

    if (depth < 0) {
        return result;
    } else {
        if (box.check()) {
            std::cout << "depth = " << depth << "\n";
            std::cout << "Complete!!\n";
            return box;
        }
    }

    for (size_t i = 0; i < box.getBottles().size(); ++i) {
        bool emptyBottleFlg = false;
        for (size_t j = 0; j < box.getBottles().size(); ++j) {
            if (j == i) continue;
            if (box.getBottles()[j].size() >= MAX_UNIT) continue;
            if (box.getBottles()[i].size() <= 0) continue;
            if (box.getBottles()[i].check()) continue;
            if (emptyBottleFlg) continue;
            if (box.getBottles()[j].empty()) {
                emptyBottleFlg = true;
            }
            if (box.getBottles()[i].monoCheck() && box.getBottles()[j].empty()) continue;
            if (!(box.getBottles()[j].empty() || box.getBottles()[i].back() == box.getBottles()[j].back())) continue;

            cnt++; // 試行回数インクリメント
            Box temp = box.deepCopy();
            // std::cout << "DEBUG: cnt = " << cnt << ", i = " << i << ", j = " << j
            //           << ", bottle[i].size() = " << temp.getBottles()[i].size()
            //           << ", bottle[j].size() = " << temp.getBottles()[j].size() << "\n";
            temp.getBottles()[i].pour(temp.getBottles()[j]);
            // std::cout << "DEBUG: After pour, temp state: ";
            // for (const auto& b : temp.getBottles()) {
            //     std::cout << "[";
            //     for (size_t k = 0; k < b.size(); ++k) {
            //         std::cout << b[k] << (k < b.size() - 1 ? "," : "");
            //     }
            //     std::cout << "]";
            // }
            // std::cout << ", check() = " << temp.check() << "\n";

            std::string md5hash = Node::makeHash(temp.getBottles());
            // std::cout << "DEBUG: md5hash = " << md5hash << "\n";
            if (Node::checkDup(md5hash)) {
                continue;
            } else {
                Node::setDup(md5hash);
            }

            Node newNode(temp);
            bool ret = node.replace(newNode, box);
            if (!ret) {
                std::cout << "Error\n";
                std::cout << "cnt = " << cnt << "\n";
                std::cout << "temp = ";
                for (const auto& b : temp.getBottles()) {
                    std::cout << "[";
                    for (size_t k = 0; k < b.size(); ++k) {
                        std::cout << b[k] << (k < b.size() - 1 ? "," : "");
                    }
                    std::cout << "]";
                }
                std::cout << "\n";
                exit(1);
            }

            result = dfs(node, temp, depth - 1);
            if (!result.getBottles().empty()) {
                break;
            }
        }
        if (!result.getBottles().empty()) {
            break;
        }
    }

    return result;
}

int main() {

    // ボトルの初期化
    // std::vector<Bottle> bottles = {
    //     Bottle({RED, SKY_BLUE, RED, YELLOW}),
    //     Bottle({MAGENTA, PINK, AQUA_GREEN, RED}),
    //     Bottle({AQUA_GREEN, YELLOW_GREEN, PURPLE, BLUE}),
    //     Bottle({SKY_BLUE, MAGENTA, ORANGE, YELLOW}),
    //     Bottle({PURPLE, PINK, ORANGE, YELLOW_GREEN}),
    //     Bottle({PURPLE, BLUE, PINK, AQUA_GREEN}),
    //     Bottle({ORANGE, YELLOW, AQUA_GREEN, PURPLE}),
    //     Bottle({SKY_BLUE, BLUE, GRAY, GRAY}),
    //     Bottle({SKY_BLUE, YELLOW_GREEN, MAGENTA, RED}),
    //     Bottle({YELLOW, MAGENTA, ORANGE, GRAY}),
    //     Bottle({YELLOW_GREEN, GRAY, PINK, BLUE}),
    //     Bottle(),
    //     Bottle()
    // };

    std::vector<Bottle> bottles = {
        Bottle({ORANGE, RED, ORANGE, RED}),
        Bottle({BLUE, BLUE, ORANGE, RED}),
        Bottle({RED, ORANGE, BLUE, BLUE}),
        Bottle(),
        Bottle()
    };
    Box box(bottles);
    // 初期化と表示
    Node::init();
    box.display();

    Node node(box);
    auto start = std::chrono::high_resolution_clock::now();
    // BFS実行
    Box answer = bfs(node);

    // DFS実行
    // Box answer = dfs(node, box, 100);

    // 結果処理
    if (!answer.getBottles().empty()) {
        node.search(answer);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << std::string(answer.getBottles().size(), '-') << std::endl;
        std::cout << "手数: " << Node::getCounter() << "手" << std::endl;
        std::cout << "経過時間: " << elapsed.count() << "秒" << std::endl;
    } else {
        std::cout << "解無し？" << std::endl;
    }

    return 0;
}
