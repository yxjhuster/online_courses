#include <list>
#include <set>
#include <iostream>
#include <limits>
#include <algorithm>

namespace my {


    ////////////////////////////////////////////////////////////////////////
    // point on the plane
    struct Point {
        Point(int x = 0, int y = 0)
            : m_x(x)
            , m_y(y)
        { }

        int m_x;
        int m_y;

        bool operator<(const Point& right) const {
            if(this->m_x == right.m_x)
                return this->m_y < right.m_y;
            else
                return this->m_x < right.m_x;
        }

        bool operator==(const Point& right) const {
            return !(*this < right) && !(right < *this);
        }
    };

    std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << p.m_x << ", " << p.m_y;
        return os;
    }

    ////////////////////////////////////////////////////////////////////////
    // segment - pair of points
    struct Segment {
        Point m_point1;
        Point m_point2;

        bool operator<(const Segment& right) const {
            if(this->m_point1 == right.m_point1)
                return this->m_point2 < right.m_point2;
            else
                return this->m_point1 < right.m_point1;
        }

        bool operator==(const Segment& right) const {
            return !(*this < right) && !(right < *this);
        }
    };

    std::ostream& operator<<(std::ostream& os, const Segment& seg) {
        os << "[(" << seg.m_point1 << "), (" << seg.m_point2 << ")]";
        return os;
    }

    ////////////////////////////////////////////////////////////////////////

    // returns slope of the line defined by two given points
    double getSlope(const Point& p1, const Point& p2) {
        return (double)(p1.m_x - p2.m_x) / (p1.m_y - p2.m_y);
    }

    // returns square of given number
    inline double square(double x) {
        return x * x;
    }
    // returns distance between two given points
    double getDistance(const Point& p1, const Point& p2) {
        auto deltaX = p1.m_x - p2.m_x;
        auto deltaY = p1.m_y - p2.m_y;
        return square(deltaX) + square(deltaY);
    }

    // scans given list of points and returns segment with maximum length
    // O(N^2) running time
    template<typename ForwardIterator>
    bool findLongestSegment(ForwardIterator first, ForwardIterator last, Segment& retVal) {
        bool res = false;
        double maxDistance = std::numeric_limits<double>::lowest();
        for(ForwardIterator p1 = first; p1 != last; ++p1) {
            ForwardIterator p2 = p1;
            while(++p2 != last) {
                double dist = getDistance(*p1, *p2);
                if(dist > maxDistance) {
                    retVal.m_point1 = std::min(*p1, *p2);
                    retVal.m_point2 = std::max(*p1, *p2);
                    maxDistance = dist;
                    res = true;
                }
            }
        }
        return res;
    }

    // returns
    Segment getSegment(const Point& p0, const Point& p1, const Point& p2, const Point& p3) {
        std::list<Point> points;
        points.push_back(p0);
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);
        Segment retVal;
        findLongestSegment(points.begin(), points.end(), retVal);
        return retVal;
    }


    template <typename ForwardIterator>
    void printRange(const char* prefix, ForwardIterator first, ForwardIterator last) {
        std::cout << prefix;
        while(first != last)
            std::cout << *(first++) << ", ";
        std::cout << std::endl;
    }
    ////////////////////////////////////////////////////////////////////////
    // finds all collinear points
    template<typename ForwardIterator, typename OutputIterator>
    void findCollinearBruteForce(ForwardIterator first, ForwardIterator last, OutputIterator result) {
        std::set<Segment> resSegments;

        for(ForwardIterator it0 = first; it0 != last; ++it0) {
            ForwardIterator it1 = it0;
            while(++it1 != last) {
                ForwardIterator it2 = it1;
                while(++it2 != last) {
                    ForwardIterator it3 = it2;
                    while(++it3 != last) {
                        double slp1 = getSlope(*it0, *it1);
                        double slp2 = getSlope(*it0, *it2);
                        double slp3 = getSlope(*it0, *it3);
                        if(slp1 == slp2 && slp2 == slp3)
                            resSegments.insert(getSegment(*it0, *it1, *it2, *it3));
                    }
                }
            }
        }

        std::copy(resSegments.begin(), resSegments.end(), result);
    }

    ////////////////////////////////////////////////////////////////////////
    // finds all collinear points
    template<typename ForwardIterator, typename OutputIterator>
    void findCollinearFast(ForwardIterator first, ForwardIterator last, OutputIterator result) {


    }

}
