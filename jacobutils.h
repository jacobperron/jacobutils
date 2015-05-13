/**
 * A collection of handy C++ functions.
 *
 * @author Jacob Perron <jperron@sfu.ca>
 */

#ifndef JACOBUTILS_H
#define JACOBUTILS_H

#include <vector>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <dirent.h>

/** Return a list of all files in a given directory with the provided suffix.
 */
static std::vector<std::string> get_files(const std::string directory, const std::string suffix){ 
    std::vector<std::string> result;
    DIR* dir = opendir(directory.c_str());

    if (!dir) return result; //empty result

    dirent* entry;
    while (entry = readdir(dir)) {
        std::string name = entry->d_name;
        if (name.size() >= suffix.size() &&
            equal(suffix.rbegin(), suffix.rend(), name.rbegin())) {
            result.push_back(name);
        }
    }

    return result;
}

/** Split a string into tokens given a delimiter.
 */
static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

/** Conversion from double to std::string.
 */
static std::string dtos(double d) {
    std::ostringstream strs;
    strs << d;
    return strs.str(); 
} 

/** Conversion from int to std::string.
 */
static std::string itos(int d) {
    std::ostringstream strs;
    strs << d;
    return strs.str(); 
} 

/** Get a timestamp for the current time in micro-seconds.
 */
typedef unsigned long long timestamp_t;
static timestamp_t get_timestamp() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_usec + (timestamp_t) now.tv_sec * 1000000;
}
#endif
