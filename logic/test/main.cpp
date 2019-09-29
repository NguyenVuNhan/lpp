#include "test_table.h"
#include "test_notation.h"
#include "test_tree.h"
#include "test_predicate.h"
#include "test_cnf.h"
#include "test_logic_manager.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
