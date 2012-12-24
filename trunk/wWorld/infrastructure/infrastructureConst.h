

// infrastructureConst.h
//

#ifndef INFRASTRUCTURE_CONST_H
#define INFRASTRUCTURE_CONST_H

/////////////////// Bit Const //////////////////
constexpr unsigned gc_bitBase = 2;			// Basic value of bit. Binary.
constexpr unsigned gc_byteBitsCnt = 9;		// Every byte has 9 bits.
constexpr unsigned gc_byteCharsCnt = 4+1;		// If 'class byte' convert 
											// to a string, it will take 4+1 
											// character at most.
constexpr unsigned gc_byteMaxVal = 512; 		// 2 ^ 9 = 512.


/////////////// Exception Const ////////////////

#endif // INFRASTRUCTURE_CONST_H
