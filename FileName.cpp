#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

// 学生类
class Student {
private:
    string studentId;    // 学号
    string name;         // 姓名
    string className;    // 班级
    vector<double> scores; // 各科成绩

public:
    // 构造函数
    Student(string id = "", string n = "", string cls = "")
        : studentId(id), name(n), className(cls) {
    }

    // 获取学号
    string getStudentId() const { return studentId; }

    // 获取姓名
    string getName() const { return name; }

    // 获取班级
    string getClassName() const { return className; }

    // 设置学号
    void setStudentId(string id) { studentId = id; }

    // 设置姓名
    void setName(string n) { name = n; }

    // 设置班级
    void setClassName(string cls) { className = cls; }

    // 添加成绩
    void addScore(double score) {
        scores.push_back(score);
    }

    // 获取成绩列表
    vector<double> getScores() const { return scores; }

    // 设置成绩列表
    void setScores(vector<double> newScores) { scores = newScores; }

    // 计算平均分
    double calculateAverage() const {
        if (scores.empty()) return 0.0;

        double sum = 0;
        for (double score : scores) {
            sum += score;
        }
        return sum / scores.size();
    }

    // 显示学生信息
    void display() const {
        cout << left << setw(12) << studentId
            << setw(10) << name
            << setw(10) << className;

        // 显示各科成绩
        for (double score : scores) {
            cout << setw(8) << fixed << setprecision(1) << score;
        }

        // 显示平均分
        cout << setw(10) << fixed << setprecision(2) << calculateAverage() << endl;
    }

    // 获取成绩数量
    int getScoreCount() const { return scores.size(); }
};

// 学生管理系统类
class StudentManagementSystem {
private:
    vector<Student> students;  // 存储所有学生
    int subjectCount;          // 科目数量

public:
    StudentManagementSystem() : subjectCount(3) {} // 默认3门科目

    // 设置科目数量
    void setSubjectCount(int count) {
        subjectCount = count;
    }

    // 获取科目数量
    int getSubjectCount() const {
        return subjectCount;
    }

    // 添加学生
    void addStudent() {
        string id, name, cls;
        vector<double> scores;

        cout << "\n=== 添加学生 ===" << endl;

        // 输入学号
        cout << "请输入学号: ";
        cin >> id;

        // 检查学号是否已存在
        for (const Student& student : students) {
            if (student.getStudentId() == id) {
                cout << "学号已存在，添加失败！" << endl;
                return;
            }
        }

        cout << "请输入姓名: ";
        cin >> name;

        cout << "请输入班级: ";
        cin >> cls;

        // 输入各科成绩
        for (int i = 1; i <= subjectCount; i++) {
            double score;
            cout << "请输入第" << i << "科成绩: ";
            cin >> score;

            // 验证成绩范围
            while (score < 0 || score > 100) {
                cout << "成绩无效，请输入0-100之间的分数: ";
                cin >> score;
            }

            scores.push_back(score);
        }

        // 创建学生对象并添加到列表
        Student newStudent(id, name, cls);
        newStudent.setScores(scores);
        students.push_back(newStudent);

        cout << "学生添加成功！" << endl;
    }

    // 删除学生
    void deleteStudent() {
        string id;

        cout << "\n=== 删除学生 ===" << endl;
        cout << "请输入要删除学生的学号: ";
        cin >> id;

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getStudentId() == id) {
                students.erase(it);
                cout << "学生删除成功！" << endl;
                return;
            }
        }

        cout << "未找到学号为 " << id << " 的学生！" << endl;
    }

    // 修改学生信息
    void modifyStudent() {
        string id;

        cout << "\n=== 修改学生信息 ===" << endl;
        cout << "请输入要修改学生的学号: ";
        cin >> id;

        for (auto& student : students) {
            if (student.getStudentId() == id) {
                int choice;
                cout << "请选择要修改的内容：" << endl;
                cout << "1. 修改姓名" << endl;
                cout << "2. 修改班级" << endl;
                cout << "3. 修改成绩" << endl;
                cout << "4. 修改全部信息" << endl;
                cout << "请选择 (1-4): ";
                cin >> choice;

                switch (choice) {
                case 1: {
                    string newName;
                    cout << "请输入新姓名: ";
                    cin >> newName;
                    student.setName(newName);
                    cout << "姓名修改成功！" << endl;
                    break;
                }
                case 2: {
                    string newClass;
                    cout << "请输入新班级: ";
                    cin >> newClass;
                    student.setClassName(newClass);
                    cout << "班级修改成功！" << endl;
                    break;
                }
                case 3: {
                    vector<double> newScores;
                    cout << "请重新输入" << subjectCount << "科成绩:" << endl;
                    for (int i = 1; i <= subjectCount; i++) {
                        double score;
                        cout << "第" << i << "科成绩: ";
                        cin >> score;

                        while (score < 0 || score > 100) {
                            cout << "成绩无效，请输入0-100之间的分数: ";
                            cin >> score;
                        }

                        newScores.push_back(score);
                    }
                    student.setScores(newScores);
                    cout << "成绩修改成功！" << endl;
                    break;
                }
                case 4: {
                    string newName, newClass;
                    vector<double> newScores;

                    cout << "请输入新姓名: ";
                    cin >> newName;
                    cout << "请输入新班级: ";
                    cin >> newClass;

                    cout << "请重新输入" << subjectCount << "科成绩:" << endl;
                    for (int i = 1; i <= subjectCount; i++) {
                        double score;
                        cout << "第" << i << "科成绩: ";
                        cin >> score;

                        while (score < 0 || score > 100) {
                            cout << "成绩无效，请输入0-100之间的分数: ";
                            cin >> score;
                        }

                        newScores.push_back(score);
                    }

                    student.setName(newName);
                    student.setClassName(newClass);
                    student.setScores(newScores);
                    cout << "学生信息修改成功！" << endl;
                    break;
                }
                default:
                    cout << "无效选择！" << endl;
                }
                return;
            }
        }

        cout << "未找到学号为 " << id << " 的学生！" << endl;
    }

    // 查询学生
    void queryStudent() {
        int choice;

        cout << "\n=== 查询学生 ===" << endl;
        cout << "1. 按学号查询" << endl;
        cout << "2. 按姓名查询" << endl;
        cout << "3. 按班级查询" << endl;
        cout << "4. 显示所有学生" << endl;
        cout << "请选择查询方式 (1-4): ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string id;
            cout << "请输入学号: ";
            cin >> id;

            bool found = false;
            for (const Student& student : students) {
                if (student.getStudentId() == id) {
                    displayHeader();
                    student.display();
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "未找到学号为 " << id << " 的学生！" << endl;
            }
            break;
        }
        case 2: {
            string name;
            cout << "请输入姓名: ";
            cin >> name;

            bool found = false;
            for (const Student& student : students) {
                if (student.getName() == name) {
                    if (!found) {
                        displayHeader();
                        found = true;
                    }
                    student.display();
                }
            }

            if (!found) {
                cout << "未找到姓名为 " << name << " 的学生！" << endl;
            }
            break;
        }
        case 3: {
            string cls;
            cout << "请输入班级: ";
            cin >> cls;

            bool found = false;
            for (const Student& student : students) {
                if (student.getClassName() == cls) {
                    if (!found) {
                        displayHeader();
                        found = true;
                    }
                    student.display();
                }
            }

            if (!found) {
                cout << "未找到班级为 " << cls << " 的学生！" << endl;
            }
            break;
        }
        case 4:
            displayAllStudents();
            break;
        default:
            cout << "无效选择！" << endl;
        }
    }

    // 显示所有学生
    void displayAllStudents() {
        if (students.empty()) {
            cout << "系统中暂无学生信息！" << endl;
            return;
        }

        cout << "\n=== 所有学生信息 ===" << endl;
        displayHeader();

        for (const Student& student : students) {
            student.display();
        }
    }

    // 显示表头
    void displayHeader() const {
        cout << left << setw(12) << "学号"
            << setw(10) << "姓名"
            << setw(10) << "班级";

        // 显示科目标题
        for (int i = 1; i <= subjectCount; i++) {
            cout << setw(8) << ("科目" + to_string(i));
        }

        cout << setw(10) << "平均分" << endl;
        cout << string(12 + 10 + 10 + 8 * subjectCount + 10, '-') << endl;
    }

    // 成绩排序
    void sortStudents() {
        if (students.empty()) {
            cout << "系统中暂无学生信息！" << endl;
            return;
        }

        int choice;
        cout << "\n=== 成绩排序 ===" << endl;
        cout << "1. 按平均分降序排列" << endl;
        cout << "2. 按平均分升序排列" << endl;
        cout << "3. 按学号排序" << endl;
        cout << "请选择排序方式 (1-3): ";
        cin >> choice;

        switch (choice) {
        case 1:
            // 按平均分降序排列
            sort(students.begin(), students.end(),
                [](const Student& a, const Student& b) {
                    return a.calculateAverage() > b.calculateAverage();
                });
            cout << "按平均分降序排列完成！" << endl;
            break;
        case 2:
            // 按平均分升序排列
            sort(students.begin(), students.end(),
                [](const Student& a, const Student& b) {
                    return a.calculateAverage() < b.calculateAverage();
                });
            cout << "按平均分升序排列完成！" << endl;
            break;
        case 3:
            // 按学号排序
            sort(students.begin(), students.end(),
                [](const Student& a, const Student& b) {
                    return a.getStudentId() < b.getStudentId();
                });
            cout << "按学号排序完成！" << endl;
            break;
        default:
            cout << "无效选择！" << endl;
            return;
        }

        displayAllStudents();
    }

    // 成绩统计
    void statistics() {
        if (students.empty()) {
            cout << "系统中暂无学生信息！" << endl;
            return;
        }

        cout << "\n=== 成绩统计 ===" << endl;

        // 计算各科平均分
        vector<double> subjectSums(subjectCount, 0.0);
        vector<double> subjectMax(subjectCount, 0.0);
        vector<double> subjectMin(subjectCount, 100.0);

        for (const Student& student : students) {
            vector<double> scores = student.getScores();
            for (int i = 0; i < subjectCount; i++) {
                subjectSums[i] += scores[i];
                if (scores[i] > subjectMax[i]) subjectMax[i] = scores[i];
                if (scores[i] < subjectMin[i]) subjectMin[i] = scores[i];
            }
        }

        // 显示各科统计信息
        cout << "科目\t平均分\t最高分\t最低分" << endl;
        cout << string(30, '-') << endl;
        for (int i = 0; i < subjectCount; i++) {
            double avg = subjectSums[i] / students.size();
            cout << "科目" << i + 1 << "\t" << fixed << setprecision(2)
                << avg << "\t" << subjectMax[i] << "\t" << subjectMin[i] << endl;
        }

        // 计算整体平均分
        double totalAvg = 0.0;
        for (const Student& student : students) {
            totalAvg += student.calculateAverage();
        }
        totalAvg /= students.size();

        cout << "\n全体学生平均分: " << fixed << setprecision(2) << totalAvg << endl;

        // 显示分数段统计
        vector<int> scoreRanges(6, 0); // 0: <60, 1: 60-69, 2: 70-79, 3: 80-89, 4: 90-99, 5: 100

        for (const Student& student : students) {
            double avg = student.calculateAverage();
            if (avg < 60) scoreRanges[0]++;
            else if (avg < 70) scoreRanges[1]++;
            else if (avg < 80) scoreRanges[2]++;
            else if (avg < 90) scoreRanges[3]++;
            else if (avg < 100) scoreRanges[4]++;
            else scoreRanges[5]++;
        }

        cout << "\n平均分分布情况:" << endl;
        cout << "不及格(<60): " << scoreRanges[0] << "人" << endl;
        cout << "及格(60-69): " << scoreRanges[1] << "人" << endl;
        cout << "中等(70-79): " << scoreRanges[2] << "人" << endl;
        cout << "良好(80-89): " << scoreRanges[3] << "人" << endl;
        cout << "优秀(90-99): " << scoreRanges[4] << "人" << endl;
        cout << "满分(100): " << scoreRanges[5] << "人" << endl;
    }

    // 生成简单报表
    void generateReport() {
        if (students.empty()) {
            cout << "系统中暂无学生信息！" << endl;
            return;
        }

        cout << "\n=== 学生成绩报表 ===" << endl;
        cout << "生成日期: 2023年" << endl;
        cout << "学生总数: " << students.size() << "人" << endl;
        cout << "科目数量: " << subjectCount << "科" << endl;

        // 显示成绩排名
        cout << "\n成绩排名:" << endl;
        displayHeader();

        // 按平均分降序排列
        vector<Student> sortedStudents = students;
        sort(sortedStudents.begin(), sortedStudents.end(),
            [](const Student& a, const Student& b) {
                return a.calculateAverage() > b.calculateAverage();
            });

        int rank = 1;
        for (const Student& student : sortedStudents) {
            cout << left << setw(4) << rank++;
            student.display();
        }

        // 显示统计摘要
        cout << "\n统计摘要:" << endl;

        // 计算前三名平均分
        double top3Avg = 0.0;
        int count = min(3, (int)sortedStudents.size());
        for (int i = 0; i < count; i++) {
            top3Avg += sortedStudents[i].calculateAverage();
        }
        top3Avg /= count;

        // 计算整体平均分
        double totalAvg = 0.0;
        for (const Student& student : students) {
            totalAvg += student.calculateAverage();
        }
        totalAvg /= students.size();

        cout << "前三名平均分: " << fixed << setprecision(2) << top3Avg << endl;
        cout << "全体平均分: " << fixed << setprecision(2) << totalAvg << endl;

        // 显示各科最高分学生
        cout << "\n单科状元:" << endl;
        for (int i = 0; i < subjectCount; i++) {
            double maxScore = 0.0;
            string topStudent;

            for (const Student& student : students) {
                vector<double> scores = student.getScores();
                if (scores[i] > maxScore) {
                    maxScore = scores[i];
                    topStudent = student.getName() + "(" + student.getStudentId() + ")";
                }
            }

            cout << "科目" << i + 1 << ": " << topStudent << " (" << maxScore << "分)" << endl;
        }
    }

    // 显示菜单
    void showMenu() {
        cout << "\n========== 学生成绩管理系统 ==========" << endl;
        cout << "1. 添加学生" << endl;
        cout << "2. 删除学生" << endl;
        cout << "3. 修改学生信息" << endl;
        cout << "4. 查询学生" << endl;
        cout << "5. 显示所有学生" << endl;
        cout << "6. 成绩排序" << endl;
        cout << "7. 成绩统计" << endl;
        cout << "8. 生成报表" << endl;
        cout << "9. 设置科目数量" << endl;
        cout << "0. 退出系统" << endl;
        cout << "======================================" << endl;
        cout << "请选择操作 (0-9): ";
    }

    // 运行系统
    void run() {
        int choice;

        // 设置科目数量
        cout << "请输入科目数量: ";
        cin >> subjectCount;
        while (subjectCount <= 0) {
            cout << "科目数量必须大于0，请重新输入: ";
            cin >> subjectCount;
        }

        do {
            showMenu();
            cin >> choice;

            switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                modifyStudent();
                break;
            case 4:
                queryStudent();
                break;
            case 5:
                displayAllStudents();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                statistics();
                break;
            case 8:
                generateReport();
                break;
            case 9:
                setSubjectCountMenu();
                break;
            case 0:
                cout << "感谢使用学生成绩管理系统，再见！" << endl;
                break;
            default:
                cout << "无效选择，请重新输入！" << endl;
            }

            // 清除输入缓冲区
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (choice != 0);
    }

    // 设置科目数量菜单
    void setSubjectCountMenu() {
        int count;
        cout << "\n当前科目数量: " << subjectCount << endl;
        cout << "请输入新的科目数量: ";
        cin >> count;

        if (count <= 0) {
            cout << "科目数量必须大于0！" << endl;
            return;
        }

        if (count != subjectCount && !students.empty()) {
            cout << "警告：更改科目数量将清空现有学生数据！是否继续？(y/n): ";
            char confirm;
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                students.clear();
                subjectCount = count;
                cout << "科目数量已更新，现有学生数据已清空！" << endl;
            }
            else {
                cout << "操作已取消！" << endl;
            }
        }
        else {
            subjectCount = count;
            cout << "科目数量已更新！" << endl;
        }
    }
};

// 主函数
int main() {
    // 设置控制台输出为UTF-8编码（Windows系统）
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    StudentManagementSystem system;
    system.run();

    return 0;
}