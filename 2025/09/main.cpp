
#include "../../helpers/extras.hh"

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::array<long,2>> points;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) break;
        std::vector<std::string> sLine = splitString(line, ",");
        const long x = atol(sLine[0].c_str());
        const long y = atol(sLine[1].c_str());
        points.push_back({x, y});
    }
    file.close();

    long ans = 0;
    for (size_t k1 = 0; k1 < points.size()-1; k1++) {
        for (size_t k2 = k1+1; k2 < points.size(); k2++) {
            long dx = points[k1][0] - points[k2][0] + 1;
            long dy = points[k1][1] - points[k2][1] + 1;
            long area = abs(dx*dy);
            if (area > ans) ans = area;
        }
    }
    std::cout << "Part 1: " << ans << '\n';
}

typedef struct {
    double x;
    double y;
} Point;

bool ray_line_segment_intersection(
    Point rayOrigin,
    Point rayDirection,
    Point p1,
    Point p2
)
{
    // Line segment vector
    Point lineVec = {p2.x - p1.x, p2.y - p1.y};

    // Vector from line segment start to ray origin
    Point v1 = {rayOrigin.x - p1.x, rayOrigin.y - p1.y};

    // Calculate the determinant of the matrix formed by rayDirection and lineVec
    // This is equivalent to the 2D cross product
    double det = rayDirection.x * lineVec.y - rayDirection.y * lineVec.x;

    // If the determinant is close to zero, the ray and line are parallel
    // or collinear. In this case, they either don't intersect or are collinear
    // and potentially overlap. We'll consider no intersection for simplicity
    // in this general case.
    if (det == 0) {
        return false;
    }

    // Calculate parameters t (for ray) and u (for line segment)
    double t = (v1.x * lineVec.y - v1.y * lineVec.x) / det;
    double u = (v1.x * rayDirection.y - v1.y * rayDirection.x) / det;

    // Check if the intersection point lies on the ray (t >= 0)
    // and on the line segment (0 <= u <= 1)
    if (t >= 0 && u >= 0 && u <= 1) {
        return true; // Intersection found
    }

    return false; // No intersection
}

bool ray_line_segment_intersection1(
    Point ray_origin,
    Point ray_direction,
    Point line_p1,
    Point line_p2
)
{
    // Line segment vector
    Point line_vec = {line_p2.x - line_p1.x, line_p2.y - line_p1.y};

    // Calculate the determinant
    double determinant = ray_direction.x * line_vec.y - ray_direction.y * line_vec.x;

    // If determinant is close to zero, lines are parallel or collinear
    if (determinant == 0) {
        // Handle collinear case if necessary (e.g., check if ray origin is on the line segment)
        return false;
    }

    // Calculate parameters t and u
    double t = ((ray_origin.x - line_p1.x) * line_vec.y - (ray_origin.y - line_p1.y) * line_vec.x) / determinant;
    double u = ((ray_origin.x - line_p1.x) * ray_direction.y - (ray_origin.y - line_p1.y) * ray_direction.x) / determinant;

    // Check if intersection occurs within the ray (t >= 0) and the line segment (0 <= u <= 1)
    if (t >= 0 && u >= 0 && u <= 1) {
        return true;
    }

    return false;
}

bool pointIsInside(
    double x,
    double y,
    std::vector<std::array<double,2>>& points // ,std::vector<bool>& GRID
) {
    // Ray comes from 0,0 and passes through x,y
    // Need to loop over the lines to see if the ray passes over it
    // No GRID (should be a hash map anyway...)
    size_t numIntersections = 0;
    Point ray_origin{0,0};
    Point ray_direction{x,y};
    for (size_t k = 0; k < points.size(); k++) {
        Point p1{
            points[(k+0) % points.size()][0],
            points[(k+0) % points.size()][1]
        };
        Point p2{
            points[(k+1) % points.size()][0],
            points[(k+1) % points.size()][1]
        };

        // Check if the ray intersects this line
        if (ray_line_segment_intersection(
            ray_origin,
            ray_direction,
            p1,
            p2
        )) numIntersections++;
    }
    return (numIntersections%2)==1;
}

bool isValidArea( // maybe try winding number?
    std::array<double,2>& p1,
    std::array<double,2>& p2,
    std::vector<std::array<double,2>>& points // ,std::vector<bool>& GRID
)
{
    size_t x1 = std::min(p1[0], p2[0]);
    size_t y1 = std::min(p1[1], p2[1]);
    size_t x2 = std::max(p1[0], p2[0]);
    size_t y2 = std::max(p1[1], p2[1]);
    for (size_t k1 = x1; k1 <= x2; k1++) {
        for (size_t k2 = y1; k2 <= y2; k2++) {
            if (k1 == p1[0] && k2 == p1[1]) continue;
            if (k1 == p2[0] && k2 == p2[1]) continue;
            if (!pointIsInside(k1+0.01, k2+0.01, points)) return false;
        }
    }
    return true;
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::array<double,2>> points;
    double maxX = 0;
    double maxY = 0;
    double minX = __LONG_MAX__;
    double minY = minX;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) break;
        std::vector<std::string> sLine = splitString(line, ",");
        const double x = atof(sLine[0].c_str());
        const double y = atof(sLine[1].c_str());
        if (x > maxX) maxX = x;
        if (y > maxY) maxY = y;
        if (minX > x) minX = x;
        if (minY > y) minY = y;
        points.push_back({x, y});
    }
    file.close();

    // Add 1 to the maxes so we can use the points as indexes
    maxX+=1.0;
    maxY+=1.0;
    printf("%f, %f\n", maxX, maxY);
    // std::vector<bool> GRID(maxX*maxY, false); // About 1GB of needed memory.... This or use a sparse matrix...
					      // This has to be wrong...
					      // I should just be able to "shoot rays" in the two directions
					      // at the corners and see if I am in a valid container...

    size_t ans = 1;
    for (auto& p1 : points) {
        for (auto& p2 : points) {
            // First check that this new square COULD be bigger
            size_t curArea = (1+std::abs(p1[0]-p2[0]))*(1+std::abs(p1[1]-p2[1]));
            if (curArea <= ans) {
                // printf("%zu < %zu: Skipping...\n", curArea, ans);
                continue;
            }
            if (isValidArea(p1, p2, points)) {
                ans = curArea;
                printf("Current Max Area: %zu\n", ans);
            } {
                // printf("Invalid Area: %zu\n", curArea);
            }
        }
    }

    std::cout << "Part 2: " << ans << '\n';
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}


// 228294 Too Low
