/**
 * @file subgroup_info.h
 *
 * @date Feb 17, 2017
 */

#pragma once

#include <cstdint>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <typeindex>
#include <vector>

#include "derecho_exception.h"

namespace derecho {

class View;
class SubView;

/**
 * An exception that indicates that a subgroup membership function was unable
 * to finish executing because its enclosing Group was not in a valid state.
 * Usually this means that the Group did not have enough members to completely
 * provision the subgroup, or specific nodes that the subgroup needed were not
 * available.
 */
class subgroup_provisioning_exception : public derecho_exception {
public:
    subgroup_provisioning_exception(const std::string& message = "") : derecho_exception(message) {}
};

/**
 * The data structure used to store a subgroups-and-shards layout for a single
 * subgroup type (i.e. Replicated Object type). The outer vector represents
 * subgroups of the same type, and the inner vector represents shards of each
 * subgroup, so the vectors map subgroup index -> shard index -> sub-view of
 * that shard.
 */
using subgroup_shard_layout_t = std::vector<std::vector<SubView>>;

/** The type of a lambda function that generates subgroup and shard views
 * for a specific subgroup type. This is a function that takes the previous View
 * and current View as input, and outputs a vector-of-vectors representing
 * subgroups and shards. */
using shard_view_generator_t = std::function<subgroup_shard_layout_t(const std::type_index&, const std::unique_ptr<View>&, View&)>;

/**
 * Container for whatever information is needed to describe a Group's subgroups
 * and shards.
 */
struct SubgroupInfo {
    /**
     * The function that generates SubViews for each subgroup and shard
     * of a given replicated type.
     */
    const shard_view_generator_t subgroup_membership_function;

    SubgroupInfo(const shard_view_generator_t& subgroup_membership_function)
            : subgroup_membership_function(subgroup_membership_function) {}
};

}  // namespace derecho
