#include "math.hpp"

namespace gamehacking::math
{
    void SinCos(float* ScalarSin, float* ScalarCos, float Value) {
        // Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
        float quotient = (INV_PI * 0.5f) * Value;
        if (Value >= 0.0f) {
            quotient = (float)((int)(quotient + 0.5f));
        }
        else {
            quotient = (float)((int)(quotient - 0.5f));
        }
        float y = Value - (2.0f * PI) * quotient;

        // Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
        float sign;
        if (y > HALF_PI) {
            y = PI - y;
            sign = -1.0f;
        }
        else if (y < -HALF_PI) {
            y = -PI - y;
            sign = -1.0f;
        }
        else {
            sign = +1.0f;
        }

        float y2 = y * y;

        // 11-degree minimax approximation
        *ScalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

        // 10-degree minimax approximation
        float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
        *ScalarCos = sign * p;
    }

    Vector3D GetClosestPointInLineFromPoint(Vector3D p1, Vector3D p2, Vector3D p)
    {
        /*
        auto slope = (p2.y_ - p1.y_) / (p2.x_ - p1.x_);

        // y - y1 = m(x - x1)
        // ay + bx + c = 0

        auto a = slope;
        auto b = -1;
        auto c = (slope * p2.x_) + (p2.y_);

        auto x1 = p.x_;
        auto y1 = p.y_;

        auto q = Vector3D((pow(b, 2) * x1 - a * b * y1 - a * c) / (pow(a, 2) + pow(b, 2)), (pow(a, 2) * y1 - a * b * x1 - b * c) / (pow(a, 2) + pow(b, 2)), 0);

        return q;
        */

        auto direction = (p2 - p1).Unit();
        auto difference_between_point_and_point_on_line = p - p2;
        auto dot_product = difference_between_point_and_point_on_line.DotProduct(direction);
        auto q = p2 + direction * dot_product;
        return q;
    }

    bool DoesPointLieInLineSegment(Vector3D p1, Vector3D p2, Vector3D p)
    {
        auto slope1 = (p - p1).Unit();
        auto slope2 = (p - p2).Unit();

        /*
        if ((int)(slope1.x_ * 1000) == -(int)(slope2.x_ * 1000) && (int)(slope1.y_ * 1000) == -(int)(slope2.y_ * 1000))
        {
            return true;
        }
        */
        if ((p.y_ - p1.y_ == 0 && p.y_ - p2.y_ == 0) || copysign(1, slope1.x_) != copysign(1, slope2.x_) && copysign(1, slope1.y_) != copysign(1, slope2.y_))
        {
            return true;
        }
        return false;
    }

    std::vector<Vector3D> GetIntersectionPointsBetweenLineAndCircle(Vector3D p1, Vector3D p2, Vector3D p, double r, bool segment)
    {
        double epsilon = 1E-10;

        std::vector<Vector3D> intersection_points;

        auto sq = [](double x)
            {
                return x * x;
            };

        auto within = [epsilon, sq](double x1, double y1, double x2, double y2, double x, double y) {
            double d1 = sqrt(sq(x2 - x1) + sq(y2 - y1));    // distance between end-points
            double d2 = sqrt(sq(x - x1) + sq(y - y1));      // distance from point to one end
            double d3 = sqrt(sq(x2 - x) + sq(y2 - y));      // distance from point to other end
            double delta = d1 - d2 - d3;
            return fabs(delta) < epsilon;   // true if delta is less than a small tolerance
        };

        auto rxy = [within](double x1, double y1, double x2, double y2, double x, double y, bool segment)
            {
                if (!segment || within(x1, y1, x2, y2, x, y))
                {
                    return true;
                }
                else {
                    return false;
                }
            };



        auto fx = [](double A, double B, double C, double x)
            {
                return -(A * x + C) / B;
            };

        auto fy = [](double A, double B, double C, double y)
            {
                return -(B * y + C) / A;
            };


        
        double x0 = p.x_, y0 = p.y_;
        double x1 = p1.x_, y1 = p1.y_;
        double x2 = p2.x_, y2 = p2.y_;
        double A = y2 - y1;
        double B = x1 - x2;
        double C = x2 * y1 - x1 * y2;
        double a = sq(A) + sq(B);
        double b, c, d;
        bool bnz = true;
        int cnt = 0;


        if (fabs(B) >= epsilon) {
            // if B isn't zero or close to it
            b = 2 * (A * C + A * B * y0 - sq(B) * x0);
            c = sq(C) + 2 * B * C * y0 - sq(B) * (sq(r) - sq(x0) - sq(y0));
        }
        else {
            b = 2 * (B * C + A * B * x0 - sq(A) * y0);
            c = sq(C) + 2 * A * C * x0 - sq(A) * (sq(r) - sq(x0) - sq(y0));
            bnz = false;
        }
        d = sq(b) - 4 * a * c; // discriminant
        if (d < 0) {
            // line & circle don't intersect
            //printf("[]\n");
            return intersection_points;
        }

        if (d == 0) {
            // line is tangent to circle, so just one intersect at most
            if (bnz) {
                double x = -b / (2 * a);
                double y = fx(A, B, C, x);
                auto success = rxy(x1, y1, x2, y2, x, y, segment);
                if (success && Vector3D::IsInFieldOfView(p1, (p2-p1).Unit(), Vector3D{ x,y,0 }))
                {
                    intersection_points.push_back(Vector3D{ x,y,0 });
                }
            }
            else {
                double y = -b / (2 * a);
                double x = fy(A, B, C, y);
                auto success = rxy(x1, y1, x2, y2, x, y, segment);
                if (success && Vector3D::IsInFieldOfView(p1, (p2 - p1).Unit(), Vector3D{ x,y,0 }))
                {
                    intersection_points.push_back(Vector3D{ x,y,0 });
                }
            }
        }
        else {
            // two intersects at most
            d = sqrt(d);
            if (bnz) {
                double x = (-b + d) / (2 * a);
                double y = fx(A, B, C, x);
                auto success = rxy(x1, y1, x2, y2, x, y, segment);
                if (success && Vector3D::IsInFieldOfView(p1, (p2 - p1).Unit(), Vector3D{ x,y,0 }))
                {
                    intersection_points.push_back(Vector3D{ x,y,0 });
                }

                x = (-b - d) / (2 * a);
                y = fx(A, B, C, x);
                success = rxy(x1, y1, x2, y2, x, y, segment);
                if (success && Vector3D::IsInFieldOfView(p1, (p2 - p1).Unit(), Vector3D{ x,y,0 }))
                {
                    intersection_points.push_back(Vector3D{ x,y,0 });
                }
            }
            else {
                double y = (-b + d) / (2 * a);
                double x = fy(A, B, C, y);
                auto success = rxy(x1, y1, x2, y2, x, y, segment);
                if (success && Vector3D::IsInFieldOfView(p1, (p2 - p1).Unit(), Vector3D{ x,y,0 }))
                {
                    intersection_points.push_back(Vector3D{ x,y,0 });
                }

                y = (-b - d) / (2 * a);
                x = fy(A, B, C, y);
                success = rxy(x1, y1, x2, y2, x, y, segment);
                if (success && Vector3D::IsInFieldOfView(p1, (p2 - p1).Unit(), Vector3D{ x,y,0 }))
                {
                    intersection_points.push_back(Vector3D{ x,y,0 });
                }
            }
        }
        
        std::vector<Vector3D> intersection_points_sorted;

        if (intersection_points.size() == 1)
        {
            intersection_points_sorted.push_back(intersection_points[0]);
        }
        else if (intersection_points.size() == 2)
        {
            if ((intersection_points[0] - p1).MagnitudeXY() < (intersection_points[1] - p1).MagnitudeXY())
            {
                intersection_points_sorted.push_back(intersection_points[0]);
                intersection_points_sorted.push_back(intersection_points[1]);
            }
            else
            {
                intersection_points_sorted.push_back(intersection_points[1]);
                intersection_points_sorted.push_back(intersection_points[0]);
            }
        }

        return intersection_points_sorted;
    }
}