#include "test_table.h"
#include "test_notation.h"
#include "test_tree.h"
#include "test_predicate.h"
#include "test_cnf.h"

#define BOOST_LOG_DYN_LINK 1
#include <boost/log/trivial.hpp>

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
