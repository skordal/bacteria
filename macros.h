/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
/*************************************************/

#ifndef MACROS_H
#define MACROS_H

#include "config_db.h"

// Plus-minus function:
#define PM(x) ((random() % x) * (random() % 2 ? 1 : -1))

// Check if an object has reached its destination:
#define AT_DESTINATION(cur_pos, dest_pos, tolerance) \
	((cur_pos.x >= (dest_pos.x - tolerance)) && \
		(cur_pos.x <= (dest_pos.x + tolerance)) && \
		(cur_pos.y >= (dest_pos.y - tolerance)) && \
		(cur_pos.y <= (dest_pos.y + tolerance)))

// Same as above, in pointer version:
//#define AT_DESTINATION_P(cur_pos, dest_pos, tolerance) ((cur_pos->x >= (dest_pos->x - tolerance)) && (cur_pos->x <= (dest_pos->x + tolerance)) && (cur_pos->y >= (dest_pos->y - tolerance)) && (cur_pos->y <= (dest_pos.y + tolerance)))

// Comparison of coordinate pairs:
#define CMP_PAIR(pair_a, pair_b) \
	((pair_a.x == pair_b.x) && (pair_a.y == pair_b.y))

// For specification of default config entries:
#define CFG_INT(name, value) {name, TYPE_INTEGER, {value, false, 0.0f, NULL}}
#define CFG_BOOL(name, value) {name, TYPE_BOOLEAN, {0, value, 0.0f, NULL}}
#define CFG_FLOAT(name, value) {name, TYPE_FLOAT, {0, false, value, NULL}}
#define CFG_STRING(name, value) {name, TYPE_STRING, {0, false, 0.0f, const_cast<char *>(value)}}
#define CFG_NULL {NULL, TYPE_INVALID, {0, false, 0.0f, NULL}}

#endif

