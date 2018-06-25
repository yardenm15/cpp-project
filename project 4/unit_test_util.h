#ifndef UNIT_TEST_UTIL_H_
#define UNIT_TEST_UTIL_H_
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

#define FAIL(msg) do {\
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << msg << std::endl;\
		return false;\
	} while(0)

#define ASSERT_TRUE(expression) do { \
                if(!((expression))) { \
                        FAIL("expression is false :: "); \
                } \
        } while (0)

#define ASSERT_FALSE(expression) do { \
                if((expression)) { \
                        FAIL("expression is true  ::"); \
                } \
		} while (0)

#define RUN_TEST(f) do { \
			if(f()==true){ \
				std::cout    << #f << ":: PASS" << std::endl;\
			}else{ std::cerr << #f << ":: FAIL"  << std::endl;\
			} }while (0)

#ifdef __cplusplus
}
#endif

#endif /* UNIT_TEST_UTIL_H_ */
