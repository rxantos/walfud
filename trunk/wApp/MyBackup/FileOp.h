

// FileOp.h
//

#pragma once

#include "PathParser.h"

/**
 *
 */
bool Copy(const PathParser &src, const PathParser &dst);
bool CreateDir(const PathParser &path);
bool Del(const PathParser &dst);