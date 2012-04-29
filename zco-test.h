#ifndef _ZCO_TEST_H_
#define _ZCO_TEST_H_

#ifndef _SYS_CDEFS_H
#include <sys/cdefs.h>
#endif

/* convenience macro */
#define DEFINE_TEST(id_num,callback)  if(id==0 || id==id_num) { callback(); }

void z_vector_test(int);
void z_string_test(int);
void z_map_test(int);

#endif
