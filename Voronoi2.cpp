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
    // overload == operator
    bool operator==(const point &other) const
    {
        double x1 = round(x * 1000) / 1000;
        double y1 = round(y * 1000) / 1000;
        double x2 = round(other.x * 1000) / 1000;
        double y2 = round(other.y * 1000) / 1000;

        return (x1 == x2 && y1 == y2);
    }
    point()
    {
        x = 0;
        y = 0;
    }
    point(double a, double b)
    {
        x = a;
        y = b;
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

double quadratic(double a, double b, double c, bool flag)
{
    if (flag)
        return (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    return (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
}

double intersection(line l, point p, bool flag)
{
    double b = 2 * (l.m * pos - p.x - l.m * p.y);
    double c = (2 * l.c * pos - pos * pos + p.x * p.x - 2 * l.c * p.y + p.y * p.y);
    double ans = quadratic(1, b, c, flag);
    ans = round(ans * 10000) / 10000;
    return ans;
}

double calc_break_p(pair<multiset<point>, bool> p)
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
    return ((x - x1) * (x - x1) + y1 * y1 - pos * pos) / (2 * (y1 - pos));
}
class compare_set
{
public:
    typedef pair<multiset<point>, bool> value_type;
    bool operator()(const pair<multiset<point>, bool> &a, const pair<multiset<point>, bool> &b) const
    {
        auto it1 = a.first.begin();
        auto it2 = b.first.begin();
        point p1 = *it1;
        point p2 = *it2;
        point p3 = *(++it1);
        point p4 = *(++it2);
        if (p1 == p2 && p3 == p4 && p1 == p3)
        {
            return a.second < b.second;
        }
        {
            return calc_break_p(a) < calc_break_p(b);
        }
        return calc_break_p(a) < calc_break_p(b);
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

struct edge
{
    point p1, p2;
    bool flag;
    edge(point a, point b, bool fla)
    {
        p1 = a;
        p2 = b;
        flag = fla;
    }
    //==operator
    bool operator==(const edge &other) const
    {   
        bool flag1 = (p1 == other.p1 && p2 == other.p2 && flag == other.flag);
        bool flag2 = (p1 == other.p2 && p2 == other.p1 && flag == other.flag);
        return (flag1 || flag2);
    }
    bool operator<(const edge &other) const
    {
        if (p1 == other.p1)
        {
            if (p2 == other.p2)
            {
                return flag < other.flag;
            }
            return p2 < other.p2;
        }
        if (p1 == other.p2)
        {
            if (p2 == other.p1)
            {
                return flag < other.flag;
            }
            return p2 < other.p1;
        }
        return p1 < other.p1;
    }
};

multiset<pair<multiset<point>, bool>, compare_set> s;
priority_queue<point, vector<point>, compare> pq;
map<edge, point> start_p;
map<edge, point> end_p;
map<multiset<point>, point> third_vertex;
map<point, bool> is_Circle_event;
void print_set()
{
    cout << "The set is\n";
    for (auto i : s)
    {
        auto a = i.first;
        auto it = a.begin();
        point p1 = *it;
        it++;
        point p2 = *it;
        cout << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << " " << i.second << endl;
        cout << "The x coordinate of intersection is " << calc_break_p(i) << endl;
    }
}
void print_edges()
{
    for (auto i : start_p)
    {
        cout << "The focal points are\n";
        point p1 = i.first.p1;
        point p2 = i.first.p2;
        p1.print();
        p2.print();
        cout << "The flag is " << i.first.flag << endl;
        cout << "The edge is\n";
        cout << i.second.x << " " << i.second.y << endl;
        cout << end_p[i.first].x << " " << end_p[i.first].y << endl;
    }
}
int remove_element(pair<multiset<point>, bool> a)
{
    auto it = s.find(a);
    if (it == s.end())
    {
        cout << "The element is not present in the set\n";
        return 0;
    }
    s.erase(it);
    return 1;
}
void handle_circle_event(point p)
{
    pos = p.y;

    if (is_valid_CE[p])
    {
        is_valid_CE[p] = 0;
        auto pts = circle_event[p];
        auto p1 = pts.first.first;
        auto p2 = pts.first.second;
        auto p3 = pts.second;
        // p_ is the circumcentre
        point p_;
        p_.x = p.x;
        p_.y = gib_y_cord(p1, p.x);

        auto it = s.upper_bound({{p, p}, 0});

        // if (it == s.end())
        // {
        //     cout << "Iterator is at end in the circle event function, the point is" << endl;
        //     it--;
        //     auto a = *it;
        //     auto it2 = (a.first).begin();
        //     auto po1 = *it2;
        //     it2++;
        //     auto po2 = *it2;
        //     po1.print();
        //     po2.print();
        //     cout << a.second << endl;

        // }

        // if (is_valid_line[{p1, p2}])
        // {
        //     is_valid_line[{p1, p2}] = 0;
        //     end_p[{p1, p2}] = p_;
        // }
        // else
        // {
        //     is_valid_line[{p1, p2}] = 1;
        //     start_p[{p1, p2}] = p_;
        // }
        // if (is_valid_line[{p2, p3}])
        // {
        //     is_valid_line[{p2, p3}] = 0;
        //     end_p[{p2, p3}] = p_;
        // }
        // else
        // {
        //     is_valid_line[{p2, p3}] = 1;
        //     start_p[{p2, p3}] = p_;
        // }
        // if (is_valid_line[{p1, p3}])
        // {
        //     is_valid_line[{p1, p3}] = 0;
        //     end_p[{p1, p3}] = p_;
        // }
        // else
        // {
        //     is_valid_line[{p1, p3}] = 1;
        //     start_p[{p1, p3}] = p_;
        // }
        if (it == s.begin())
        {
            cout << "There is some error in handling circle event\n";
            return;
        }
        multiset<point> temp;
        it--;
        auto a = *it;
        auto it2 = (a.first).begin();
        auto po1 = *it2;
        it2++;
        auto po2 = *it2;
        temp.insert(po1);
        temp.insert(po2);
        cout << "The upper bound break point is\n";
        po1.print();
        po2.print();
        cout << a.second << endl;
        if (it == s.begin())
        {
            cout << "There is some error in handling circle event\n";
            return;
        }
        it--;
        auto b = *it;
        it2 = (b.first).begin();
        po1 = *it2;
        it2++;
        po2 = *it2;
        cout << "The previous break point is\n";
        po1.print();
        po2.print();
        cout << b.second << endl;
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
        if (not_target.size() != 2)
        {
            cout << "The not_target set is wrong\n";
            return;
        }
        cout << "The target is\n";
        target.print();
        print_set();
        for (point i : not_target)
        {
            bool flag = false;
            double x_cord = calc_break_p({{target, i}, 1});
            x_cord = round(x_cord * 1000) / 1000;
            double x_cord2 = round(p.x * 1000) / 1000;
            if (x_cord == x_cord2)
            {
                flag = true;
            }
            multiset<point> temp_ms = {target, i};
            auto temp_pair = make_pair(temp_ms, flag);
            cout << "The size of set before erasing is " << s.size() << "\n";
            if (!remove_element(temp_pair))
                return;
            cout << "The size of set after erasing is " << s.size() << "\n";

            edge e(target, i, flag);
            end_p[e] = p_;
            cout << "Erased breakpoint\n";

            cout << target.x << " " << target.y << " " << i.x << " " << i.y << " " << flag << endl;
            print_set();
        }
        auto iter = not_target.begin();
        po1 = *iter;
        iter++;
        po2 = *iter;

        bool flag = false;

        double x_cord = calc_break_p({{po1, po2}, 1});
        x_cord = round(x_cord * 1000) / 1000;
        double x_cord2 = round(p.x * 1000) / 1000;
        if (x_cord == x_cord2)
            flag = true;
        cout << "Inserting new breakpoint\n";
        s.insert({{po1, po2}, flag});
        print_set();
        edge e(po1, po2, flag);
        start_p[e] = p_;
    }
    return;
}
pair<point, point> gib_prev_curr(multiset<point> a)
{
    auto it = a.begin();
    auto p1 = *it;
    it++;
    auto p2 = *it;
    return {p1, p2};
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

    auto it = s.upper_bound({{p, p}, 0});
    if (it == s.end())
    {
        cout << "Iterator is at end" << endl;
        it--;
        point p1, p2;
        p1 = gib_prev_curr(it->first).first;
        p2 = gib_prev_curr(it->first).second;

        double y1 = gib_y_cord(p1, p.x);
        double y2 = gib_y_cord(p2, p.x);
        if (y1 < y2)
        {
            s.insert({{p, p1}, 0});
            s.insert({{p, p1}, 1});
            point inter(p.x, y1);
            edge e1(p, p1, 0);
            edge e2(p, p1, 1);
            cout << "Are the two edges same" << (e1 == e2) << endl;
            cout << " Is the edge1 already present " << (start_p.find(e1) != start_p.end()) << endl;
            cout << " Is the edge2 already present " << (start_p.find(e2) != start_p.end()) << endl;
            start_p[e1] = inter;
            start_p[e2] = inter;
        }
        else
        {
            s.insert({{p, p2}, 0});
            s.insert({{p, p2}, 1});
            point inter(p.x, y2);
            edge e1(p, p2, 0);
            edge e2(p, p2, 1);
            cout << "Are the two edges same" << (e1 == e2) << endl;
            cout << " Is the edge1 already present " << (start_p.find(e1) != start_p.end()) << endl;
            cout << " Is the edge2 already present " << (start_p.find(e2) != start_p.end()) << endl;
            start_p[e1] = inter;
            start_p[e2] = inter;
        }
        cout << "Inserted new arcs" << endl;
        print_set();
        point p_ = return_circle_eve({{p1, p2}, p});

        if (p_.y < pos)
        {
            circle_event[p_] = {{p1, p2}, p};
            is_valid_CE[p_] = 1;
            is_Circle_event[p_] = 1;
            cout << "Pushed new circle event\n";
            pq.push(p_);
        }

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

    double y1 = gib_y_cord(p1, p.x);
    double y2 = gib_y_cord(p2, p.x);
    point p_ = return_circle_eve({{p1, p2}, p});

    if (p_.y < pos)
    {
        circle_event[p_] = {{p1, p2}, p};
        is_valid_CE[p_] = 1;
        is_Circle_event[p_] = 1;
        cout << "Pushed new circle event\n";
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
        y1 = gib_y_cord(p1, p.x);
        y2 = gib_y_cord(p2, p.x);
        point target = p1;
        double y_in = y1;
        if (y1 > y2)
        {
            target = p2;
            y_in = y2;
        }
        // Add new arcs
        point inter(p.x, y_in);
        s.insert({{p, target}, 0});
        s.insert({{p, target}, 1});

        edge e1(p, target, 0);
        edge e2(p, target, 1);
        cout << "Is e1 > e2 " << (e2 < e1) << endl;
        cout << "Adding new edges: ";
        cout << p.x << " " << p.y << " " << target.x << " " << target.y << "\n";
        cout << inter.x << " " << inter.y << "\n";
        auto it1 = start_p.find(e1);
        if (it1 != start_p.end())
        {

            cout << " The edge1 already present " << ((*it1).first).p1.x << " " << ((*it1).first).p1.y << " " << ((*it1).first).p2.x << " " << ((*it1).first).p2.y << "\n";
        }
        auto it2 = start_p.find(e2);
        if (it1 != start_p.end())
        {

            cout << " The edge2 already present " << e2.p1.x << " " << e2.p1.y << " " << e2.p2.x << " " << e2.p2.y << "\n";
        }
        start_p[e1] = inter;
        start_p[e2] = inter;
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
    pos = pq.top().y;
    pq.pop();
    double x_in1 = p1.x;
    double y_in1 = gib_y_cord(p0, x_in1);
    point inter1(x_in1, y_in1);
    edge e1(p1, p0, 1);
    edge e2(p1, p0, 0);

    start_p[e1] = inter1;
    start_p[e2] = inter1;
    pos = pq.top().y;
    s.insert({{p1, p0}, 1});
    s.insert({{p1, p0}, 0});

    while (!pq.empty())
    {
        point pt = pq.top();
        pq.pop();
        cout << "The next event is " << pt.x << " " << pt.y << endl;
        if (is_Circle_event[pt])
        {
            cout << "Circle event" << endl;
            handle_circle_event(pt);
        }
        else
        {
            cout << "Site event" << endl;
            handle_site_event(pt);
        }
        cout << "The current position is " << pos << endl;
        print_set();
        cout << "The edges are\n";
        print_edges();
        cout << "End of Event\n\n\n";
    }

    print_edges();

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