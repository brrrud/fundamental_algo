#ifndef SANDBOX_CPP_BPLUS_TREE_H
#define SANDBOX_CPP_BPLUS_TREE_H

#include <stack>
#include "associative_container.h"
#include "search_tree.h"
#include "exception/not_implemented.h"
#include "../logger/logger.h"
#include "../logger/logger_holder.h"
#include "../memory/memory.h"
#include "../memory/memory_holder.h"

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
class bplus_tree final:
    public search_tree<tkey, tvalue, tkey_comparer>
{

private:

    class bplus_tree_node_interaction_context final:
        public search_tree<tkey, tvalue, tkey_comparer>::node_interaction_context
    {

    public:

        bplus_tree_node_interaction_context(
            logger *logger,
            memory *allocator)
            : search_tree<tkey, tvalue, tkey_comparer>::node_interaction_context(logger, allocator)
        {

        }

    public:

        typename search_tree<tkey, tvalue, tkey_comparer>::node_interaction_context::node_split_mode get_split_mode() const noexcept override
        {
            return search_tree<tkey, tvalue, tkey_comparer>::node_interaction_context::node_split_mode::copy_median_kvp;
        }

    };

private:

    unsigned int _t;

private:

    typename search_tree<tkey, tvalue, tkey_comparer>::node_interaction_context *create_node_interaction_context(
        logger *logger,
        memory *allocator) const noexcept override
    {
        return new bplus_tree_node_interaction_context(logger, allocator);
    }

public:

    explicit bplus_tree(
        unsigned int t,
        memory *allocator = nullptr,
        logger *logger = nullptr)
        : search_tree<tkey, tvalue, tkey_comparer>(create_node_interaction_context(logger, allocator), allocator, logger),
          _t(t)
    {

    }

public:

    bplus_tree(bplus_tree<tkey, tvalue, tkey_comparer> const &other)
        : search_tree<tkey, tvalue, tkey_comparer>(other), _t(other._t)
    {

    }

    bplus_tree<tkey, tvalue, tkey_comparer> &operator=(bplus_tree<tkey, tvalue, tkey_comparer> const &other)
    {
        if (this == &other)
        {
            return *this;
        }

        static_cast<search_tree<tkey, tvalue, tkey_comparer> &>(*this) = other;
        _t = other._t;

        return *this;
    }

    bplus_tree(bplus_tree<tkey, tvalue, tkey_comparer> &&other) noexcept
        : search_tree<tkey, tvalue, tkey_comparer>(std::move(other)), _t(other._t)
    {
        other._t = 0;
    }

    bplus_tree<tkey, tvalue, tkey_comparer> &operator=(bplus_tree<tkey, tvalue, tkey_comparer> &&other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        static_cast<search_tree<tkey, tvalue, tkey_comparer> &>(*this) = std::move(other);
        _t = other._t;
        other._t = 0;

        return *this;
    }

    ~bplus_tree() = default;

private:

    std::tuple<std::stack<typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node *>,
               typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node **,
               unsigned int,
               bool> find_path(tkey const &key)
    {
        std::stack<typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node *> path;
        typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node **iterator = &(search_tree<tkey, tvalue, tkey_comparer>::_root);
        unsigned int target_key_index = 0;
        tkey_comparer comparer;

        while (*iterator != nullptr)
        {
            // TODO: dihotomy search

            auto gone_to_subtree = false;
            auto i = 0;
            for (; i < (*iterator)->involved_keys; ++i)
            {
                auto comparison_result = comparer((*iterator)->keys_and_values[i].key, key);
                if (comparison_result == 0)
                {
                    if ((*iterator)->subtrees[0] == nullptr)
                    {
                        return { path, iterator, i, true };
                    }

                    path.push(*iterator);
                    iterator = (*iterator)->subtrees + i + 1;
                    gone_to_subtree = true;

                   

                    break;
                }
                else if (comparison_result > 0)
                {
                    if ((*iterator)->subtrees[0] == nullptr)
                    {
                        return { path, iterator, i, false };
                    }

                    path.push(*iterator);
                    iterator = (*iterator)->subtrees + i;
                    gone_to_subtree = true;
                    break;
                }
            }

            if (gone_to_subtree)
            {
                continue;
            }

            if (i == (*iterator)->involved_keys)
            {
                if ((*iterator)->subtrees[0] == nullptr)
                {
                    return { path, iterator, i, false };
                }

                path.push(*iterator);
                iterator = (*iterator)->subtrees + (*iterator)->involved_keys;
            }
        }

        return { path, iterator, target_key_index, false };
    }

public:

    void iterate_tree()
    {
        iterate_tree_inner(search_tree<tkey, tvalue, tkey_comparer>::_root, 0);
    }

    void iterate_tree_inner(search_tree<tkey, tvalue, tkey_comparer>::search_tree_node *ptr, unsigned int tab)
    {
       if (ptr == nullptr)
       {
           return;
       }

       for (auto j = 0; j < tab; j++)
       {
           std::cout << "  ";
       }
       std::cout << "[ ";

       for (auto i = 0; i < ptr->involved_keys; i++)
       {
           std::cout << '{' << ptr->keys_and_values[i].key << " " << ptr->keys_and_values[i].value << "} ";
       }

       std::cout << ']' << std::endl;
       if (ptr->subtrees[0] != nullptr)
       {
           for (auto i = 0; i <= ptr->involved_keys; i++)
           {
               iterate_tree_inner(ptr->subtrees[i], tab + 1);
           }
       }
    }

    void iterate_terminal_nodes_list()
    {
       auto *ptr = search_tree<tkey, tvalue, tkey_comparer>::_root;
       while (ptr->subtrees[0] != nullptr)
       {
           ptr = ptr->subtrees[0];
       }
       std::cout << "[ ";
       while (true)
       {
           std::cout << "[";
           for (auto i = 0; i < ptr->involved_keys; i++)
           {
               std::cout << ptr->keys_and_values[i].key;
               if (i != ptr->involved_keys - 1)
               {
                   std::cout << ", ";
               }
           }
           std::cout << "]";

           ptr = ptr->subtrees[ptr->involved_keys];
           if (ptr != nullptr)
           {
               std::cout << ", ";
           }
           else
           {
               std::cout << " ]";
               break;
           }
       }
    }

    void insert(
        tkey const &key,
        tvalue &&value) override
    {
        auto path_info = find_path(key);
        if (std::get<3>(path_info))
        {
            throw typename search_tree<tkey, tvalue, tkey_comparer>::insertion_exception();
        }

        auto subtrees_for_new_root = insert_inner(key, std::move(value), path_info);
        if (subtrees_for_new_root.has_value())
        {
            search_tree<tkey, tvalue, tkey_comparer>::_root = search_tree<tkey, tvalue, tkey_comparer>::_context->create_node_shell(get_min_keys_count());
            search_tree<tkey, tvalue, tkey_comparer>::_root->involved_keys = 1;
            search_tree<tkey, tvalue, tkey_comparer>::_root->keys_and_values[0].key = std::get<2>(subtrees_for_new_root.value());
            search_tree<tkey, tvalue, tkey_comparer>::_root->subtrees[0] = std::get<0>(subtrees_for_new_root.value());
            search_tree<tkey, tvalue, tkey_comparer>::_root->subtrees[1] = std::get<1>(subtrees_for_new_root.value());
        }
    }

private:

    std::optional<std::tuple<typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node *, typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node *, tkey> > insert_inner(
        tkey const &key,
        tvalue &&value,
        std::tuple<std::stack<typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node *>, typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node **, unsigned int, bool> path_info)
    {
        auto **target_ptr = std::get<1>(path_info);

        if (*target_ptr == nullptr)
        {
            *target_ptr = search_tree<tkey, tvalue, tkey_comparer>::_context->create_node_shell(get_min_keys_count());
            (*target_ptr)->involved_keys++;
            new ((*target_ptr)->keys_and_values) typename associative_container<tkey, tvalue>::key_value_pair;
            (*target_ptr)->keys_and_values[0].key = key;
            (*target_ptr)->keys_and_values[0].value = std::move(value);
            (*target_ptr)->subtrees[0] = (*target_ptr)->subtrees[1] = nullptr;

            return std::nullopt;
        }

        auto path_to_target = std::get<0>(path_info);
        auto target_index = std::get<2>(path_info);

        auto result = search_tree<tkey, tvalue, tkey_comparer>::_context->shift(*target_ptr, target_index, key, std::move(value), (*target_ptr)->subtrees[(*target_ptr)->involved_keys]);
        if (!result.has_value())
        {
            return std::nullopt;
        }

        tkey_comparer comparer;

        typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node *parent = *target_ptr;

        while (!path_to_target.empty())
        {
            parent = path_to_target.top();
            path_to_target.pop();

            auto index = 0;
            for (; index < parent->involved_keys; index++)
            {
                if (comparer(parent->keys_and_values[index].key, result.value().second.key) > 0)
                {
                    break;
                }
            }

            result = search_tree<tkey, tvalue, tkey_comparer>::_context->shift(parent, index, result.value().second.key, std::move(value), result.value().first);
            if (!result.has_value())
            {
                return std::nullopt;
            }
        }

        return std::make_optional<std::tuple<typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node *, typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node *, tkey> >(std::tuple<typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node *, typename search_tree<tkey, tvalue, tkey_comparer>::search_tree_node *, tkey>(parent, result.value().first, result.value().second.key));
    }

public:

    tvalue const &get(
        tkey const &key) override
    {
        auto path_info = find_path(key);
        if (!std::get<3>(path_info))
        {
            throw typename search_tree<tkey, tvalue, tkey_comparer>::reading_exception();
        }

        return (*std::get<1>(path_info))->keys_and_values[std::get<2>(path_info)].value;
    }

    std::vector<typename associative_container<tkey, tvalue>::key_value_pair> get_in_range(
        tkey const &lower_bound_inclusive,
        tkey const &upper_bound_inclusive) override
    {
        tkey_comparer comparer;
        if (comparer(lower_bound_inclusive, upper_bound_inclusive) > 0)
        {
            return std::vector<typename associative_container<tkey, tvalue>::key_value_pair>(0);
        }

        std::vector<typename associative_container<tkey, tvalue>::key_value_pair> result;
        auto path_info = find_path(lower_bound_inclusive);
        auto index = std::get<2>(path_info);
        auto *traversable_node = *std::get<1>(path_info);

        while (traversable_node != nullptr)
        {
            for (auto i = index; i < traversable_node->involved_keys; i++)
            {
                if (comparer(traversable_node->keys_and_values[i].key, upper_bound_inclusive) > 0)
                {
                    return result;
                }

                result.push_back(traversable_node->keys_and_values[i]);
            }

            traversable_node = traversable_node->subtrees[traversable_node->involved_keys];
            index = 0;
        }

        return result;
    }

    tvalue remove(
        tkey const &key) override
    {
        auto path_info = find_path(key);
        if (!std::get<3>(path_info))
        {
            throw typename search_tree<tkey, tvalue, tkey_comparer>::removing_exception();
        }

    
        throw not_implemented("not implemented");
    }

private:

    [[nodiscard]] inline unsigned int get_min_keys_count() const noexcept
    {
        return _t - 1;
    }

    [[nodiscard]] inline unsigned int get_max_keys_count() const noexcept
    {
        return get_min_keys_count() * 2;
    }

};

#endif //SANDBOX_CPP_BPLUS_TREE_H
