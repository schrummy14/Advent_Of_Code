
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

bool isValidArea(
    std::array<long, 2>& p1,
    std::array<long, 2>& p2,
    std::vector<std::array<long, 2>>& points
)
{
    long x1 = std::min(p1[0], p2[0]);
    long y1 = std::min(p1[1], p2[1]);
    long x2 = std::max(p1[0], p2[0]);
    long y2 = std::max(p1[1], p2[1]);

    const size_t numPoints = points.size();

    for (size_t k = 0; k < numPoints; k++) {
        size_t id1 = (k+0) % numPoints;
        size_t id2 = (k+1) % numPoints;
        long p1x = std::min(points[id1][0], points[id2][0]);
        long p1y = std::min(points[id1][1], points[id2][1]);
        long p2x = std::max(points[id1][0], points[id2][0]);
        long p2y = std::max(points[id1][1], points[id2][1]);
        long mx = (p2x+p1x)/2;
        long my = (p2y+p1y)/2;

        if (
            (x1 < p1x && p1x < x2) &&
            (y1 < p1y && p1y < y2)
        ) {
            return false;
        }

        if (
            (x1 < p2x && p2x < x2) &&
            (y1 < p2y && p2y < y2)
        ) {
            return false;
        }

        // Also check the midpoint of a line segment
        if (
            (x1 < mx && mx < x2) &&
            (y1 < my && my < y2)
        ) {
            return false;
        }

        // The rectangle does not contain any other points...
        // Now we need to check that the lines DO NOT CROSS another line
        if (p2x-p1x == 0) { // vertical line
            // Need to check only the horizontal lines of the rectangle
            if (!(x1 < p1x && p1x < x2)) continue;
            if (!(p1y < y1 && y1 < p2y)) continue;
            return false;
        } else { // horizontal line
            // Need to check only the vertical lines of the rectangle
            if (!(y1 < p1y && p1y < y2)) continue;
            if (!(p1x < x1 && x1 < p2x)) continue;
            return false;
        }

    }

    return true;
}

void doPart2(const char* filename)
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

    std::array<long,2> r1{0,0};
    std::array<long,2> r2{0,0};
    size_t ans = 1;
    for (size_t k1 = 0; k1 < points.size()-1; k1++) {
        auto p1 = points[k1];
        for (size_t k2 = k1+1; k2 < points.size(); k2++) {
            auto p2 = points[k2];
            // First check that this new square COULD be bigger
            size_t curArea = (1+std::abs(p1[0]-p2[0]))*(1+std::abs(p1[1]-p2[1]));
            if (curArea <= ans) {
                continue;
            }
            if (isValidArea(p1, p2, points)) {
                ans = curArea;
                r1 = p1;
                r2 = p2;
                printf("Current Max Area: %zu\n", ans);
            }
        }
    }

    printf(
        "Part 2: %zu (%ld %ld %ld %ld)\n",
        ans, r1[0], r1[1], r2[0], r2[1]
    );
    // std::cout << "Part 2: " << ans << '\n';
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
