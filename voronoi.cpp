#include <iostream>
#include <set>
#include <map>
#include <bits/stdc++.h>
#include <queue>
#include <cmath>
using namespace std;

double pos;
double min_x = 1000000, min_y = 1000000, max_x = -1000000, max_y = -1000000;
struct point
{
    double x, y;
    typedef double value_type;                // Define value_type
    typedef allocator<double> allocator_type; // Define allocator_type

    point()
    {
        x = 0;
        y = 0;
    }
    point(double a, double b)
    {
        // round off a to 3 decimal places
        x = round(a * 1000) / 1000;
        // round off b to 2 decimal places
        y = round(b * 1000) / 1000;
    }
    bool operator<(const point &other) const
    {
        return (x != other.x) ? (x < other.x) : (y < other.y);
    }
    void print()
    {
        cout << x << " " << y << endl;
    }
};

map<point, pair<pair<point, point>, point>> circle_event;
map<point, bool> is_valid_CE;
struct line
{
    double m, c;
    line() : m(0), c(0) {}
    line(double a, double b) : m(a), c(b) {}
};
point boundary_p(point p1, point p2, point p3)
{
    double m = (p1.y - p2.y) / (p1.x - p2.x);
    double c_ = (p1.y * p2.x - p2.y * p1.x) / (p2.x - p1.x);
    line l_j(m, c_);
    m = -1 / m;
    c_ = (p2.y * p2.y - p1.y * p1.y + p2.x * p2.x - p1.x * p1.x) / (2 * (p2.y - p1.y));
    line l_p(m, c_);
    return p1;
}

double quadratic(double a, double b, double c, bool flag)
{
    if (flag)
        return (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    return (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
}

double intersection(line l, point p, bool flag)
{
    double b = 2 * (l.m * pos - p.x - l.m * p.y);
    double c = (2 * l.c * pos - pos * pos + p.x * p.x - 2 * l.c * p.y);

    return quadratic(1, b, c, flag);
}

double call_funcs(pair<multiset<point>, bool> p)
{
    auto a = p.first;
    bool flag = p.second;
    auto it = a.begin();
    auto p1 = *(it);
    it++;
    auto p2 = *it;

    if (p1.x == p2.x && p1.y == p2.y)
    {
        return p1.x;
    }
    double m = (p1.y - p2.y) / (p1.x - p2.x);
    m = -1 / m;
    double c_ = (p2.y * p2.y - p1.y * p1.y + p2.x * p2.x - p1.x * p1.x) / (2 * (p2.y - p1.y));
    line l(m, c_);
    return intersection(l, p1, flag);
}
point line_int(line l1, line l2)
{
    point p;
    p.x = (l2.c - l1.c) / (l1.m - l2.m);
    p.y = l1.m * p.x + l1.c;
    return p;
}
double gib_y_cord(point p, double x)
{
    auto y1 = p.y;
    auto x1 = p.x;
    return (x - x1) * (x - x1) + (y1 * y1 - pos * pos) / (y1 - pos);
}
class compare_set
{
public:
    typedef pair<multiset<point>, bool> value_type;
    bool operator()(const pair<multiset<point>, bool> &a, const pair<multiset<point>, bool> &b) const
    {
        return call_funcs(a) < call_funcs(b);
    }
};

class compare
{
public:
    typedef point value_type;
    bool operator()(const point &a, const point &b) const
    {
        return a.y < b.y;
    }
};
multiset<pair<multiset<point>, bool>, compare_set> s;
priority_queue<point, vector<point>, compare> pq;
map<multiset<point>, bool> is_valid_line;
map<multiset<point>, point> start_p;
map<multiset<point>, point> end_p;
map<multiset<point>, point> third_vertex;
map<point, bool> is_Circle_event;
void print_set()
{
    for (auto i : s)
    {
        auto a = i.first;
        auto it = a.begin();
        point p1 = *it;
        it++;
        point p2 = *it;
        cout << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << " " << i.second << endl;
    }
}
void handle_circle_event(point p)
{
    pos = p.y;

    if (is_valid_CE[p])
    {
        auto pts = circle_event[p];
        point p1 = pts.first.first;
        point p2 = pts.first.second;
        point p3 = pts.second;
        double m1 = -(p1.x - p2.x) / (p1.y - p2.y);
        double m2 = -(p1.x - p3.x) / (p1.y - p3.y);
        double c1 = (p1.y + p2.y) / 2 - m1 * (p1.x + p2.x) / 2;
        double c2 = (p1.y + p3.y) / 2 - m2 * (p1.x + p3.x) / 2;
        line l1(m1, c1);
        line l2(m2, c2);
        point p_ = line_int(l1, l2);
        is_valid_CE[p] = 0;
        auto it = s.upper_bound({{p, p}, 0});

        if (it == s.end())
        {
            cout << "Iterator is at end in the circle event function" << endl;
            it--;
        }
        if (is_valid_line[{p1, p2}])
        {
            is_valid_line[{p1, p2}] = 0;
            end_p[{p1, p2}] = p_;
        }
        else
        {
            is_valid_line[{p1, p2}] = 1;
            start_p[{p1, p2}] = p_;
        }
        if (is_valid_line[{p2, p3}])
        {
            is_valid_line[{p2, p3}] = 0;
            end_p[{p2, p3}] = p_;
        }
        else
        {
            is_valid_line[{p2, p3}] = 1;
            start_p[{p2, p3}] = p_;
        }
        if (is_valid_line[{p1, p3}])
        {
            is_valid_line[{p1, p3}] = 0;
            end_p[{p1, p3}] = p_;
        }
        else
        {
            is_valid_line[{p1, p3}] = 1;
            start_p[{p1, p3}] = p_;
        }
        it--;
        multiset<point> temp;
        auto a = *it;
        auto it2 = (a.first).begin();
        auto po1 = *it2;
        it2++;
        auto po2 = *it2;
        temp.insert(po1);
        temp.insert(po2);
        cout << "The upper bound is\n";
        po1.print();
        po2.print();
        cout << a.second << endl;
        if (it == s.begin())
        {
            cout << "The iterator is at the beginning" << endl;
        }
        it--;
        auto b = *it;
        it2 = (b.first).begin();
        po1 = *it2;
        it2++;
        po2 = *it2;
        temp.insert(po1);
        temp.insert(po2);
        point target;
        set<point> not_target;

        for (auto i : temp)
        {
            if (temp.count(i) == 2)
            {
                cout << "found target" << endl;
                target = i;
            }

            else
                not_target.insert(i);
        }
        for (auto i : not_target)
        {
            bool flag = false;
            double x_cord = call_funcs({{target, i}, 1});
            if (x_cord == p.x)
                flag = true;
            s.erase({{target, i}, flag});
        }
        auto iter = not_target.begin();
        po1 = *iter;
        iter++;
        po2 = *iter;

        bool flag = false;

        double x_cord = call_funcs({{po1, po2}, 1});
        if (x_cord == p.x)
            flag = true;
        s.insert({{po1, po2}, flag});
    }
    return;
}
point return_circle_eve(pair<pair<point, point>, point> a)
{
    auto p1 = a.first.first;
    auto p2 = a.first.second;
    auto p3 = a.second;
    double m1 = -(p1.x - p2.x) / (p1.y - p2.y);
    double m2 = -(p1.x - p3.x) / (p1.y - p3.y);
    double c1 = (p1.y + p2.y) / 2 - m1 * (p1.x + p2.x) / 2;
    double c2 = (p1.y + p3.y) / 2 - m2 * (p1.x + p3.x) / 2;
    line l1(m1, c1);
    line l2(m2, c2);
    point p_ = line_int(l1, l2);
    double dist = sqrt((p_.x - p1.x) * (p_.x - p1.x) + (p_.y - p1.y) * (p_.y - p1.y));
    p_.y -= dist;
    return p_;
}
void handle_site_event(point p)
{
    pos = p.y;
    if (s.size() == 1)
    {
        auto it = (s.begin()->first).begin();
        point p1 = *it;
        it++;
        point p2 = *it;
        double y1 = gib_y_cord(p1, p.x);
        double y2 = gib_y_cord(p2, p.x);
        point target = p1;
        if (y2 < y1)
        {
            target = p2;
        }
        s.insert({{p, target}, 0});
        s.insert({{p, target}, 1});
        point p_ = return_circle_eve({{p1, p2}, p});
        if (p_.y < pos)
        {
            circle_event[p_] = {{p1, p2}, p};
            is_valid_CE[p_] = 1;
            is_Circle_event[p_] = 1;
            pq.push(p_);
        }
    }
    else
    {
        double x = call_funcs({{p, p}, 0});
        auto it = s.upper_bound({{p, p}, 0});
        cout << "x is " << x << endl;
        if (it == s.end())
        {
            cout << "Iterator is at end" << endl;
            it--;
            auto a = *it;
            auto it2 = (a.first).begin();
            auto p1 = *it2;
            it2++;
            auto p2 = *it2;
            double y1 = gib_y_cord(p1, x);
            double y2 = gib_y_cord(p2, x);

            point p_ = return_circle_eve({{p1, p2}, p});

            if (p_.y < pos)
            {
                circle_event[p_] = {{p1, p2}, p};
                is_valid_CE[p_] = 1;
                is_Circle_event[p_] = 1;
                pq.push(p_);
            }
            if (y1 < y2)
            {
                s.insert({{p, p1}, 0});
                s.insert({{p, p1}, 1});
            }
            else
            {
                s.insert({{p, p2}, 0});
                s.insert({{p, p2}, 1});
            }
            cout << "Inserted new arcs" << endl;
            return;
        }

        multiset<point> temp;
        auto a = *it;
        auto it2 = (a.first).begin();
        auto p1 = *it2;
        it2++;
        auto p2 = *it2;
        temp.insert(p1);
        temp.insert(p2);

        double y1 = gib_y_cord(p1, x);
        double y2 = gib_y_cord(p2, x);
        point p_ = return_circle_eve({{p1, p2}, p});

        if (p_.y < pos)
        {
            circle_event[p_] = {{p1, p2}, p};
            is_valid_CE[p_] = 1;
            is_Circle_event[p_] = 1;
            pq.push(p_);
        }

        if (it != s.begin())
        {
            it--;
            a = *it;
            it2 = (a.first).begin();
            p1 = *it2;
            it2++;
            p2 = *it2;

            temp.insert(p1);
            temp.insert(p2);
            y1 = gib_y_cord(p1, x);
            y2 = gib_y_cord(p2, x);
            point target = p1;
            if (y1 > y2)
            {
                target = p2;
            }
            // Add new arcs
            s.insert({{p, target}, 0});
            s.insert({{p, target}, 1});
            // Add new circle event
            p_ = return_circle_eve({{p1, p2}, p});

            if (p_.y < pos && !is_valid_CE[p_])
            {
                circle_event[p_] = {{p1, p2}, p};
                is_valid_CE[p_] = 1;
                is_Circle_event[p_] = 1;
                pq.push(p_);
            }
        }

        // Not sure if this is necessary

        // if (temp.size() >= 3)
        // {
        //     auto it = temp.begin();
        //     auto p1 = *it;
        //     it++;
        //     auto p2 = *it;
        //     if (p1.x == p2.x && p1.y == p2.y)
        //     {
        //         it++;
        //         p2 = *it;
        //     }
        //     it++;
        //     auto p3 = *it;
        //     if (p2.x == p3.x && p2.y == p3.y)
        //     {
        //         it++;
        //         p3 = *it;
        //     }
        //     point p_ = return_circle_eve({{p1, p2}, p3});
        //     is_valid_CE[p_] = 0;
        // }
    }
    return;
}

int main()
{

    int n;
    cin >> n;
    point pts[n];
    for (int i = 0; i < n; i++)
    {
        double x, y;
        cin >> x >> y;
        pts[i].x = x;
        pts[i].y = y;
        pq.push(pts[i]);
    }
    point p0 = pq.top();
    pq.pop();
    point p1 = pq.top();
    pq.pop();

    s.insert({{p1, p0}, 1});
    s.insert({{p1, p0}, 0});
    cout << "The size of set is " << s.size() << endl;
    while (!pq.empty())
    {
        point pt = pq.top();
        pq.pop();
        cout << pt.x << " " << pt.y << endl;
        if (is_Circle_event[pt])
        {
            cout << "circle event" << endl;
            handle_circle_event(pt);
        }
        else
        {
            cout << "site event" << endl;
            handle_site_event(pt);
        }
        cout << "The set is \n";
        print_set();
    }

    for (auto i : start_p)
    {
        cout << i.second.x << " " << i.second.y << endl;
        cout << end_p[i.first].x << " " << end_p[i.first].y << endl;
    }

    // find min x , min y, max x, max y

    // for (auto i : s)
    // {
    //     auto it = (i.first).begin();

    //     auto p1 = *it;
    //     it++;
    //     auto p2 = *it;
    //     min_x = min(min_x, min(p1.x, p2.x));
    //     max_x = max(max_x, max(p1.x, p2.x));
    //     min_y = min(min_y, min(p1.y, p2.y));
    //     max_y = max(max_y, max(p1.y, p2.y));
    // }
    // min_x -= 10;
    // max_x += 10;
    // min_y -= 10;
    // max_y += 10;
    // for (auto i : is_valid_line)
    // {
    //     if (i.second)
    //     {
    //         auto p1 = *(i.first.begin());
    //         auto it = i.first.begin();
    //         it++;
    //         auto p2 = *it;
    //     }
    // }
}