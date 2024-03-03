
#include <bits/stdc++.h>
using namespace std;

double pos;
double min_x = 100000, min_y = 100000, max_x = -100000, max_y = -100000;
struct point
{
    bool valid = true;
    double x, y;
    typedef double value_type;                // Define value_type
    typedef allocator<double> allocator_type; // Define allocator_type
    // overload == operator
    bool operator==(const point &other) const
    {
        double x1 = x;
        double y1 = y;
        double x2 = other.x;
        double y2 = other.y;

        return (fabs(x1 - x2) < 0.00000001 && fabs(y1 - y2) < 0.00000001);
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
        // std:://cout << x << " " << y << "  ";
    }
    bool operator!=(const point &other) const
    {
        return !(*this == other);
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
        return (-b + sqrt(fabs(b * b - 4 * a * c))) / (2 * a);
    return (-b - sqrt(fabs(b * b - 4 * a * c))) / (2 * a);
}

double intersection(line l, point p, bool flag)
{
    double b = 2 * (l.m * pos - p.x - l.m * p.y);
    double c = (2 * l.c * pos - pos * pos + p.x * p.x - 2 * l.c * p.y + p.y * p.y);
    double ans = quadratic(1, b, c, flag);
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
    if (p1 == p2)
    {
        return p1.x;
    }
    if (fabs(p1.y - p2.y) < 0.00000001)
    {
        return (p1.x + p2.x) / 2;
    }
    double m = -(p1.x - p2.x) / (p1.y - p2.y);
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
    if (fabs(y1 - pos) < 0.00000001)
    {
        return y1;
    }
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
        if (fabs(calc_break_p(a) - calc_break_p(b)) < 0.00000001)
        {
            return a.second < b.second;
        }
        // if (fabs(calc_break_p(a) - calc_break_p(b)) < 0.00000001)
        // {
        //     auto it1 = a.first.begin();
        //     auto it2 = b.first.begin();
        //     point p1 = *it1;
        //     point p2 = *it2;
        //     if (p1 == p2)
        //     {
        //         it1++;
        //         it2++;
        //         p1 = *it1;
        //         p2 = *it2;
        //         if (p1 == p2)
        //         {
        //             return a.second < b.second;
        //         }
        //         return p1 < p2;
        //         it1--;
        //         it2--;
        //         p1 = *it1;
        //         p2 = *it2;
        //     }
        //     return p1 < p2;
        // }
        return calc_break_p(a) < calc_break_p(b);
    }
};

class compare
{
public:
    typedef point value_type;
    bool operator()(const point &a, const point &b) const
    {
        if (fabs(a.y - b.y) < 0.00000001)
        {
            return a.x < b.x;
        }
        return a.y < b.y;
    }
};
double range_x;
double range_y;
struct edge
{
    point p1, p2;
    bool flag;
    edge(point a, point b, bool fla)
    {
        p1 = a;
        p2 = b;
        if (a.x < b.x)
        {
            p1 = a;
            p2 = b;
        }
        else
        {
            p1 = b;
            p2 = a;
        }
        flag = fla;
    }
    //==operator
    bool operator==(const edge &other) const
    {
        // Check if the points and flags match in either order
        return (p1 == other.p1 && p2 == other.p2 && flag == other.flag) ||
               (p1 == other.p2 && p2 == other.p1 && flag == other.flag);
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
multiset<edge> edges;
map<multiset<point>, point> third_vertex;
map<point, bool> is_Circle_event;
map<edge, bool> end_determined;
void print_set()
{
    // std:://cout << "THE SET\n";
    for (auto i : s)
    {
        auto a = i.first;
        auto it = a.begin();
        point p1 = *it;
        it++;
        point p2 = *it;
        // std:://cout << "FP1: ";
        // std:://cout << p1.x << " " << p1.y << " ";
        // std:://cout << "FP2: ";
        // std:://cout << p2.x << " " << p2.y << " ";
        // std:://cout << "Flag: " << i.second << " ";
        // std:://cout << "X coordinate: " << calc_break_p(i) << "\n";
    }
}

int remove_element(pair<multiset<point>, bool> a)
{
    auto it = s.lower_bound(a);
    if (it == s.end())
    {
        // std:://cout << "The element is not present in the set\n";
        return 0;
    }
    while (true)
    {
        if (it == s.end())
        {
            // std:://cout << "The element is not present in the set\n";
            return 0;
        }
        if (*it == a)
        {
            // std:://cout << "FOUND ELEMENT\n";
            break;
        }
        it++;
    }
    // std:://cout << "DELETING ELEMENT\n";
    s.erase(it);
    return 1;
}
point return_circle_eve(pair<pair<point, point>, point> a)
{
    auto p1 = a.first.first;
    auto p2 = a.first.second;
    auto p3 = a.second;
    if (fabs(p1.y - p2.y) < 0.00000001)
    {
        point p_;
        if (fabs(p1.y - p3.y) < 0.00000001)
        {
            p_.valid = false;
            return p_;
        }

        double m = -(p1.x - p3.x) / (p1.y - p3.y);
        double c = (p1.y + p3.y) / 2 - m * (p1.x + p3.x) / 2;
        double x = (p1.x + p2.x) / 2;
        p_.x = x;
        p_.y = m * x + c;
        double dist = sqrt((p_.x - p1.x) * (p_.x - p1.x) + (p_.y - p1.y) * (p_.y - p1.y));
        p_.y -= dist;
        return p_;
    }

    if (fabs(p1.y - p3.y) < 0.00000001)
    {
        point p_;
        if (fabs(p1.y - p2.y) < 0.00000001)
        {
            p_.valid = false;
            return p_;
        }
        double m = -(p1.x - p2.x) / (p1.y - p2.y);
        double c = (p1.y + p2.y) / 2 - m * (p1.x + p2.x) / 2;
        double x = (p1.x + p3.x) / 2;
        p_.x = x;
        p_.y = m * x + c;
        double dist = sqrt((p_.x - p1.x) * (p_.x - p1.x) + (p_.y - p1.y) * (p_.y - p1.y));
        p_.y -= dist;
        return p_;
    }

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
void insert_circle_event(pair<multiset<point>, bool> left, pair<multiset<point>, bool> right, point target)
{
    // PRINT SET LEFT AND RIGHT
    // std:://cout << "The left set is\n";
    // for (auto i : left.first)
    // {
    //     i.print();
    // }
    // // std:://cout << "\n";
    // // std:://cout << "The right set is\n";
    // for (auto i : right.first)
    // {
    //     i.print();
    // }
    // std:://cout << "\n";
    auto set1 = left.first;
    auto set2 = right.first;
    auto it1 = set1.begin();
    auto it2 = set2.begin();
    point p1 = *it1;
    point p2 = *it2;
    it1++;
    point p3 = *it1;
    it2++;
    point p4 = *it2;
    if (p1 == p2 && p3 == p4 && p1 == p3)
    {
        return;
    }
    // identify the three points which are not equal to target
    multiset<point> temp = {p1, p2, p3, p4};
    temp.erase(target);
    // return circle event of these three points of the set
    auto it = temp.begin();
    point p5 = *it;
    it++;
    point p6 = *it;
    point p7;
    if (temp.size() == 2)
    {
        p7 = target;
    }
    else
    {
        it++;
        p7 = *it;
    }

    if (p5 == p6 || p6 == p7 || p5 == p7)
    {
        // std:://cout << "The set is wrong\n";
        return;
    }
    // std:://cout << "The three points are\n";
    // std:://cout << "\n";

    if (fabs(p5.y - p6.y) > 0.00000001 && fabs(p6.y - p7.y) > 0.00000001)
    {
        // cout << "I AM HERE 1\n";
        double m1 = -(p5.x - p6.x) / (p5.y - p6.y);
        double m2 = -(p6.x - p7.x) / (p6.y - p7.y);
        if (fabs(m1 - m2) < 0.00000001)
        {
            // std:://cout << "The points are collinear\n";
            return;
        }
    }

    else if (fabs(p5.y - p6.y) < 0.00000001 && fabs(p7.y - p6.y) > 0.00000001)
    {
        // cout << "I AM HERE 2\n";
        double m1 = -(p6.x - p7.x) / (p6.y - p7.y);
        double x = (p5.x + p6.x) / 2;
        double y = m1 * (x - (p6.x + p7.x) / 2) + (p6.y + p7.y) / 2;
        point p_(x, y);
        if (p_.y - pos < 0.00000001 && fabs(p_.y - pos) > 0.00000001 && p_.valid)
        {
            circle_event[p_] = {{p5, p6}, p7};
            is_valid_CE[p_] = 1;
            is_Circle_event[p_] = 1;
            // std:://cout << "Pushed new circle event\n";
            // std:://cout << "The circle event is ";
            // std:://cout << "\n";
            pq.push(p_);
        }
        return;
    }

    else if (fabs(p7.y - p6.y) < 0.00000001 && fabs(p5.y - p6.y) > 0.00000001)
    {
        // cout << "I AM HERE 3\n";
        double m1 = -(p6.x - p5.x) / (p6.y - p5.y);
        double x = (p7.x + p6.x) / 2;
        double y = m1 * (x - (p6.x + p5.x) / 2) + (p6.y + p5.y) / 2;
        point p_(x, y);
        if (p_.y - pos < 0.00000001 && fabs(p_.y - pos) > 0.00000001 && p_.valid)
        {
            circle_event[p_] = {{p5, p6}, p7};
            is_valid_CE[p_] = 1;
            is_Circle_event[p_] = 1;
            // std:://cout << "Pushed new circle event\n";
            // std:://cout << "The circle event is ";
            // p_.print();
            // std:://cout << "\n";
            pq.push(p_);
        }
        return;
    }

    else
    {
        // cout << "I AM HERE 4\n";
        // std:://cout << "The points are collinear\n";
        return;
    }

    point p_ = return_circle_eve({{p5, p6}, p7});
    // cout << "I AM HERE 5\n";

    if (p_.y - pos < 0.00000001 && fabs(p_.y - pos) > 0.00000001 && p_.valid)
    {
        circle_event[p_] = {{p5, p6}, p7};
        is_valid_CE[p_] = 1;
        is_Circle_event[p_] = 1;
        // std:://cout << "Pushed new circle event\n";
        // std:://cout << "The circle event is ";
        // p_.print();
        // std:://cout << "\n";
        pq.push(p_);
    }
    return;
}
void handle_circle_event(point p)
{
    pos = p.y;

    if (is_valid_CE[p])
    {
        int found_upper = 0;
        int found_lower = 0;
        bool found_a = false;
        bool found_b = false;
        is_valid_CE[p] = 0;
        auto pts = circle_event[p];
        auto p1 = pts.first.first;
        auto p2 = pts.first.second;
        auto p3 = pts.second;
        // std:://cout << "The focal points are: ";
        // p1.print();
        // p2.print();
        // p3.print();
        // std:://cout << "\n";

        // p_ is the circumcentre
        point p_;
        p_.x = p.x;
        p_.y = gib_y_cord(p1, p.x);

        auto it = s.upper_bound({{p, p}, 0});

        if (it == s.begin())
        {
            auto ater = *it;
            // std:://cout << "The Iterator is at s.begin\n";
            if (fabs(calc_break_p(ater) - p.x) < 0.00000001)
            {

                it++;
                if (it == s.end())
                {
                    is_valid_CE[p] = 0;
                    return;
                }
                ater = *it;
                if (fabs(calc_break_p(ater) - p.x) < 0.00000001)
                {
                    it++;
                }
            }
            else
                return;
        }
        multiset<point> temp;

        it--;
        // print_set();
        auto a = *it;
        auto up = a;
        auto lo = a;
        auto it2 = (a.first).begin();
        auto po1 = *it2;
        if (calc_break_p(a) - p.x < 0 && fabs(calc_break_p(a) - p.x) > 0.00000001)
        {
            found_lower = 1;

            while (true && it != s.end())
            {
                a = *it;
                double x_temp = calc_break_p(a);
                // std:://cout << "x_temp is " << x_temp << " p.x is " << p.x << "\n";
                if (fabs(x_temp - p.x) < 0.00000001)
                {
                    found_a = true;
                    // std:://cout << "Breaking" << "\n";
                    break;
                }
                if (it == s.end())
                {
                    // std:://cout << "RETURNING" << "\n";
                    is_valid_CE[p] = 0;
                    return;
                }
                lo = a;
                it++;
                // std:://cout << "IN HERE" << "\n";
            }
            it++;
            a = *it;
            if (it != s.end())
            {
                it++;
                if (it != s.end())
                {
                    found_upper = 1;
                    up = *it;
                }
                else
                    found_upper = -1;
                it--;
            }
            else
                found_upper = -1;
        }
        else if (calc_break_p(a) > p.x && fabs(calc_break_p(a) - p.x) > 0.00000001)
        {
            found_upper = 1;
            while (true)
            {
                double x_temp = calc_break_p(a);
                // std:://cout << "x_temp is " << x_temp << " p.x is " << p.x << "\n";
                if (fabs(x_temp - p.x) < 0.00000001)
                {
                    found_a = true;
                    // std:://cout << "Breaking" << "\n";
                    break;
                }
                if (it == s.begin())
                {
                    // std:://cout << "RETURNING" << "\n";
                    is_valid_CE[p] = 0;
                    return;
                }
                it--;
                a = *it;
                // std:://cout << "IN hERE " << "\n";
            }
            if (it != s.begin())
            {
                it--;
                lo = *it;
                found_lower = 1;
                it++;
            }
            else
                found_lower = -1;
        }
        else
        {
            found_a = true;
        }
        if (!found_a)
        {
            // std:://cout << "The circle event is not valid\n";
            is_valid_CE[p] = 0;
            return;
        }

        a = *it;
        // std:://cout << "The x-cord of a is " << calc_break_p(a) << " " << p.x << "\n";
        it2 = (a.first).begin();
        po1 = *it2;
        it2++;
        auto po2 = *it2;
        temp.insert(po1);
        temp.insert(po2);
        // std:://cout << "The break point is of focii" << "\n";
        // po1.print();
        // po2.print();
        // std:://cout << a.second << "\n";
        if (it == s.begin())
        {
            auto b = a;
            it++;
            a = *it;
        }

        it--;
        auto b = *it;
        bool b_ahead = false;
        if (fabs(calc_break_p(b) - p.x) > 0.00000001)
        {
            found_lower = 1;
            lo = b;
            it++;
            it++;
            b_ahead = true;
            // Modify this
            b = *it;

            it++;
            if (it != s.end())
            {
                found_upper = 1;
                up = *it;
            }
            else
                found_upper = -1;
            it--;

            if (fabs(calc_break_p(b) - p.x) > 0.00000001)
            {
                // std:://cout << "THERE IS SOME ERROR IN CIRCLE EVENT HANDLING" << "\n";
                return;
            }
        }
        else
        {
            if (it != s.begin())
            {
                it--;
                lo = *it;
                found_lower = 1;
                it++;
            }
            else
                found_lower = -1;
            it++;
            it++;
            if (it != s.end())
            {
                found_upper = 1;
                up = *it;
            }
            else
                found_upper = -1;
        }

        // std:://cout << "The x-cord of b is " << calc_break_p(b) << " " << p.x << "\n";
        // std:://cout << "The break point is of focii" << "\n";
        it2 = (b.first).begin();
        po1 = *it2;
        it2++;
        po2 = *it2;
        // po1.print();
        // po2.print();
        // std:://cout << b.second << "\n";
        temp.insert(po1);
        temp.insert(po2);
        point target;
        set<point> not_target;
        for (auto i : temp)
        {
            if (temp.count(i) == 2)
            {
                // std:://cout << "found target" << "\n";
                target = i;
            }

            else
                not_target.insert(i);
        }
        if (not_target.size() != 2)
        {
            // std:://cout << "The not_target set is wrong" << "\n";
            return;
        }
        // std:://cout << "The target is" << "\n";
        // target.print();
        // std:://cout << "\n";
        s.erase(a);
        s.erase(b);
        for (point i : not_target)
        {
            bool flag = false;
            double x_cord = calc_break_p({{target, i}, 1});
            double x_cord2 = p.x;
            if (fabs(x_cord - x_cord2) < 0.00000001)
            {
                flag = true;
            }
            edge e(target, i, flag);
            auto it = edges.find(e);
            if (it != edges.end())
            {
                // std:://cout << "This edge was started some time ago\n";
                end_p[*it] = p_;
                end_determined[*it] = 1;
            }
            else
                end_p[e] = p_;
            end_determined[e] = 1;
            // std:://cout << "Erased breakpoint\n";

            // std:://cout << target.x << " " << target.y << " " << i.x << " " << i.y << " " << flag << "\n";
        }
        auto iter = not_target.begin();
        po1 = *iter;
        iter++;
        po2 = *iter;

        bool flag = false;

        double x_cord = calc_break_p({{po1, po2}, 1});
        double x_cord2 = p.x;
        if (fabs(x_cord - x_cord2) < 0.00000001)
            flag = true;
        // std:://cout << "Inserting new breakpoint\n";
        s.insert({{po1, po2}, flag});
        // print_set();
        edge e(po1, po2, flag);
        start_p[e] = p_;
        edges.insert(e);
        // Add circle events
        if (found_lower == 1)
        {
            if (b_ahead)
                insert_circle_event(lo, b, target);
            else
                insert_circle_event(lo, a, target);
        }
        if (found_upper == 1)
        {
            auto some = up.first;
            auto it = some.begin();
            auto p1 = *it;
            it++;
            auto p2 = *it;
            // cout << "The upper set is " << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << "\n";
            if (b_ahead)
                insert_circle_event(a, up, target);
            else
                insert_circle_event(b, up, target);
        }
    }
    else
    {
        // std:://cout << "The circle event is not valid\n";
        is_valid_CE[p] = 0;
        return;
    }

    return;
}
bool inside_box(point p)
{
    if (p.x < (min_x) || p.x > (max_x) || p.y < (min_y) || p.y > (max_y))
        return false;
    return true;
}
point check_BB_intersection(point init, point curr)
{
    if (inside_box(curr))
        return curr;
    if (fabs(init.x - curr.x) < 0.00000001)
    {
        if (curr.y < min_y)
            return point(curr.x, min_y);
        if (curr.y > max_y)
            return point(curr.x, max_y);
    }
    double m = (curr.y - init.y) / (curr.x - init.x);
    double c = curr.y - m * curr.x;
    if (curr.x < min_x)
        curr = point(min_x, m * min_x + c);
    if (curr.x > max_x)
        curr = point(max_x, m * max_x + c);
    if (curr.y < min_y)
        curr = point((min_y - c) / m, min_y);
    if (curr.y > max_y)
        curr = point((max_y - c) / m, max_y);
    return curr;
}
point intersection_point(point focus1, point focus2, bool flag)
{
    double x1 = calc_break_p({{focus1, focus2}, flag});
    double y1 = gib_y_cord(focus1, x1);
    return point(x1, y1);
}
void print_edges()
{
    for (auto i : start_p)
    {

        // std:://cout << i.second.x << " " << i.second.y << " ";
        // std:://cout << end_p[i.first].x << " " << end_p[i.first].y << "\n";
    }
}
void print_edges2()
{
    for (auto i : start_p)
    {

        std::cout << i.second.x * range_x << " " << i.second.y * range_y << "\n";
        if (end_determined[i.first])
        {
            if (inside_box(end_p[i.first]))
                std::cout << end_p[i.first].x * range_x << " " << end_p[i.first].y * range_y << "\n";
            else
            {
                point ans = check_BB_intersection(i.second, end_p[i.first]);
                std::cout << ans.x * range_x << " " << ans.y * range_y << "\n";
            }
        }
        else
        {
            point b1;
            b1 = intersection_point(i.first.p1, i.first.p2, i.first.flag);
            point ans = check_BB_intersection(i.second, b1);
            std::cout << ans.x * range_x << " " << ans.y * range_y << "\n";
        }
    }
}
pair<point, point> gib_prev_curr(multiset<point> a)
{
    auto it = a.begin();
    auto p1 = *it;
    it++;
    auto p2 = *it;
    return {p1, p2};
}

void handle_site_event(point p)
{
    pos = p.y;
    // std:://cout << "Handling site event\n";
    auto it = s.upper_bound({{p, p}, 0});

    if (it == s.end())
    {
        // std:://cout << "Iterator is at end" << "\n";
        it--;
        point p1, p2;
        p1 = gib_prev_curr(it->first).first;
        p2 = gib_prev_curr(it->first).second;

        double y1 = gib_y_cord(p1, p.x);
        double y2 = gib_y_cord(p2, p.x);
        if (y1 < y2)
        {
            if (fabs(p.y - p1.y) > 0.00000001)
            {
                s.insert({{p, p1}, 0});
                // std:://cout << "The x cordinate is " << calc_break_p({{p, p1}, 0}) << "\n";
                s.insert({{p, p1}, 1});
                // std:://cout << "The x cordinate is " << calc_break_p({{p, p1}, 1}) << "\n";
            }
            else
            {
                s.insert({{p, p1}, 0});
                // std:://cout << "The x cordinate is " << calc_break_p({{p, p1}, 0}) << "\n";
            }
            point inter(calc_break_p({{p, p1}, 0}), y1);

            edge e1(p, p1, 0);
            edge e2(p, p1, 1);
            start_p[e1] = inter;
            edges.insert(e1);
            start_p[e2] = inter;
            edges.insert(e2);
        }
        else
        {
            if (fabs(p.y - p2.y) > 0.00000001)
            {
                s.insert({{p, p2}, 0});
                // std:://cout << "The x cordinate is " << calc_break_p({{p, p2}, 0}) << "\n";
                s.insert({{p, p2}, 1});
                // std:://cout << "The x cordinate is " << calc_break_p({{p, p2}, 1}) << "\n";
            }
            else
            {
                s.insert({{p, p2}, 0});
                // std:://cout << "The x cordinate is " << calc_break_p({{p, p2}, 0}) << "\n";
            }
            point inter(calc_break_p({{p, p2}, 0}), y2);
            edge e1(p, p2, 0);
            edge e2(p, p2, 1);
            start_p[e1] = inter;
            edges.insert(e1);
            start_p[e2] = inter;
            edges.insert(e2);
        }
        // std:://cout << "Inserted new arcs" << "\n";
        // print_set();
        point p_ = return_circle_eve({{p1, p2}, p});

        if (p_.y < pos)
        {
            circle_event[p_] = {{p1, p2}, p};
            is_valid_CE[p_] = 1;
            is_Circle_event[p_] = 1;
            // std:://cout << "Pushed new circle event\n";
            // std:://cout << "The circle event is ";
            // p_.print();
            // std:://cout << "\n";
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

    if (p_.y - pos < 0.00000001)
    {
        circle_event[p_] = {{p1, p2}, p};
        is_valid_CE[p_] = 1;
        is_Circle_event[p_] = 1;
        // std:://cout << "Pushed new circle event\n";
        // std:://cout << "The circle event is ";
        // p_.print();
        // std:://cout << "\n";
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
        point inter(calc_break_p({{p, target}, 0}), y_in);
        if (fabs(p.y - target.y) > 0.00000001)
        {
            s.insert({{p, target}, 0});
            // std:://cout << "The x cordinate is " << calc_break_p({{p, target}, 0}) << "\n";
            s.insert({{p, target}, 1});
            // std:://cout << "The x cordinate is " << calc_break_p({{p, target}, 0}) << "\n";
        }
        else
        {
            s.insert({{p, target}, 0});
            // std:://cout << "The x cordinate is " << calc_break_p({{p, target}, 0}) << "\n";
        }

        edge e1(p, target, 0);
        edge e2(p, target, 1);
        // std:://cout << "Adding new edges: ";
        // std:://cout << p.x << " " << p.yb1) << " " << target.x << " " << target.y << "\n";
        // std:://cout << inter.x << " " << inter.y << "\n";
        start_p[e1] = inter;
        edges.insert(e1);
        start_p[e2] = inter;
        edges.insert(e2);
        // Add new circle event

        p_ = return_circle_eve({{p1, p2}, p});

        if (p_.y - pos < 0.00000001)
        {
            circle_event[p_] = {{p1, p2}, p};
            is_valid_CE[p_] = 1;
            is_Circle_event[p_] = 1;
            pq.push(p_);
            // std:://cout << "Pushed new circle event\n";
            // std:://cout << "The circle event is ";
            // p_.print();
            // std:://cout << "\n";
        }
        return;
    }
    if (it == s.begin())
    {
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
        point inter(calc_break_p({{p, target}, 0}), y_in);
        if (fabs(p.y - target.y) > 0.00000001)
        {
            s.insert({{p, target}, 0});
            // std:://cout << "The x cordinate is " << calc_break_p({{p, target}, 0}) << "\n";
            s.insert({{p, target}, 1});
            // std:://cout << "The x cordinate is " << calc_break_p({{p, target}, 0}) << "\n";
        }
        else
        {
            s.insert({{p, target}, 0});
            // std:://cout << "The x cordinate is " << calc_break_p({{p, target}, 0}) << "\n";
        }

        edge e1(p, target, 0);
        edge e2(p, target, 1);
        // std:://cout << "Adding new edges: ";
        // std:://cout << p.x << " " << p.y << " " << target.x << " " << target.y << "\n";
        // std:://cout << inter.x << " " << inter.y << "\n";
        start_p[e1] = inter;
        edges.insert(e1);
        start_p[e2] = inter;
        edges.insert(e2);
        return;
    }
}
void update_boundaries(point p)
{
    min_x = min(min_x, p.x);
    min_y = min(min_y, p.y);
    max_x = max(max_x, p.x);
    max_y = max(max_y, p.y);
}
void handle_inputs(point pts[], int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0, 1e-6);

    for (int i = 0; i < n; i++)
    {
        pts[i].x += distribution(gen);
        pts[i].x = pts[i].x / range_x;
        pts[i].y += distribution(gen);
        pts[i].y = pts[i].y / range_y;
    }
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
        min_x = min(min_x, pts[i].x);
        min_y = min(min_y, pts[i].y);
        max_x = max(max_x, pts[i].x);
        max_y = max(max_y, pts[i].y);
    }
    range_x = max_x - min_x;
    range_y = max_y - min_y;
    handle_inputs(pts, n);
    for (int i = 0; i < n; i++)
    {
        pq.push(pts[i]);
    }

    point p0 = pq.top();

    pq.pop();
    point p1 = pq.top();
    pos = pq.top().y;
    pq.pop();
    double x_in1 = calc_break_p({{p1, p0}, 0});
    double y_in1 = gib_y_cord(p0, x_in1);
    point inter1(x_in1, y_in1);
    edge e1(p1, p0, 1);
    edge e2(p1, p0, 0);

    start_p[e1] = inter1;
    edges.insert(e1);
    start_p[e2] = inter1;
    edges.insert(e2);
    pos = pq.top().y;
    if (fabs(p1.y - p0.y) > 0.00000001)
    {
        s.insert({{p1, p0}, 1});
        s.insert({{p1, p0}, 0});
    }
    else
    {
        s.insert({{p1, p0}, 1});
    }

    while (!pq.empty())
    {
        point pt = pq.top();
        pq.pop();
        if (is_Circle_event[pt])
        {
            handle_circle_event(pt);
        }
        else
        {
            handle_site_event(pt);
        }
    }
    cout << "\n------COMPUTATION DONE------\n";
    for (auto i : pts)
    {
        update_boundaries(i);
    }
    pos -= 10;
    // set min max;
    // for (auto i : start_p)
    // {
    //     point p1 = i.second;
    //     update_boundaries(p1);
    //     // if (end_determined[i.first])
    //     // {
    //     //     point p2 = end_p[i.first];
    //     //     update_boundaries(p2);
    //     // }
    // }
    min_x -= 1;
    min_y -= 1;
    max_x += 1;
    max_y += 1;
    pos--;
    print_edges2();
    cout << min_x << " " << min_y << "\n";
    cout << max_x << " " << min_y << "\n";
    cout << max_x << " " << max_y << "\n";
    cout << min_x << " " << max_y << "\n";
    cout << max_x << " " << min_y << "\n";
    cout << max_x << " " << max_y << "\n";
    cout << min_x << " " << max_y << "\n";
    cout << min_x << " " << min_y << "\n";
}