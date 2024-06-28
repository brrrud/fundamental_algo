#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "binary_search_tree.h"

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
class red_black_tree final : public binary_search_tree<tkey, tvalue, tkey_comparer> {
public:
    enum class color_node {
        RED,
        BLACK
    };

    struct red_black_node final : public binary_search_tree<tkey, tvalue, tkey_comparer>::node {
        color_node color;
    };

public:
    void prefix_traverse() {
        prefix_traverse_inner(
                reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(this->get_root()),
                0);
    }

private:
    void prefix_traverse_inner(typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *rb_node,
                               unsigned int depth) {
        if (rb_node == nullptr) {
            return;
        }

        for (auto i = 0; i < depth; i++) {
            std::cout << "  ";
        }
        std::cout << "Key == " << rb_node->key << ", color == " << (rb_node->color == color_node::RED ? "red" : "black")
                  << std::endl;

        prefix_traverse_inner(
                reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(rb_node->left_subtree_address),
                depth + 1);
        prefix_traverse_inner(
                reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(rb_node->right_subtree_address),
                depth + 1);
    }

private:
    class red_black_insertion_template_method final
            : public binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method {
    private:
        enum class balance_status {
            NO_BALANCE_NEEDED,
            BALANCE_AT_GP,
            BALANCE_AT_P
        };

        enum class rise_status {
            FROM_LEFT_SUBTREE,
            FROM_RIGHT_SUBTREE,
            NOTHING
        };

    private:
        red_black_tree<tkey, tvalue, tkey_comparer> *_tree;
        balance_status _balance_status;
        rise_status _rise_further_status;
        rise_status _rise_near_status;

    private:
        size_t get_node_size() const override;

        void call_constructor_node(
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *mem) const override;

        void initialize_node_additional_data(
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *mem) const override;

        void inject_additional_data(
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *from,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *to) const override;

    protected:
        void before_insert() override {
            _balance_status = balance_status::BALANCE_AT_GP;
            _rise_further_status = rise_status::NOTHING;
            _rise_near_status = rise_status::NOTHING;
        };

        void after_insert_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive) override;

    public:
        explicit red_black_insertion_template_method(
                red_black_tree<tkey, tvalue, tkey_comparer> *tree);
    };

private:
    class red_black_removing_template_method final
            : public binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method {
    private:
        enum class rise_status_remove {
            FROM_LEFT_SUBTREE,
            FROM_RIGHT_SUBTREE,
            NOTHING
        };

    private:
        red_black_tree<tkey, tvalue, tkey_comparer> *_tree;
        rise_status_remove _rise_further_status;
        rise_status_remove _rise_near_status;

    protected:
        void after_remove_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
                std::list<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive) override;

    protected:
        void before_remove() override {
            _rise_further_status = rise_status_remove::NOTHING;
            _rise_near_status = rise_status_remove::NOTHING;
        };

    public:
        explicit red_black_removing_template_method(
                red_black_tree<tkey, tvalue, tkey_comparer> *tree);
    };

public:
    explicit red_black_tree(memory *allocator = nullptr,
                            logger *logger = nullptr);

    red_black_tree(
            red_black_tree<tkey, tvalue, tkey_comparer> const &other);

    red_black_tree(
            red_black_tree<tkey, tvalue, tkey_comparer> &&other) noexcept;

    red_black_tree &operator=(
            red_black_tree<tkey, tvalue, tkey_comparer> const &other);

    red_black_tree &operator=(
            red_black_tree<tkey, tvalue, tkey_comparer> &&other) noexcept;


private:
    color_node get_color(red_black_node *current_node) const noexcept;
};

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
size_t red_black_tree<tkey, tvalue, tkey_comparer>::red_black_insertion_template_method::get_node_size() const {
    return sizeof(typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node);
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void red_black_tree<tkey, tvalue, tkey_comparer>::red_black_insertion_template_method::call_constructor_node(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *mem) const {
    new(mem) typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void red_black_tree<tkey, tvalue, tkey_comparer>::red_black_insertion_template_method::initialize_node_additional_data(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *mem) const {
    reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(mem)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void red_black_tree<tkey, tvalue, tkey_comparer>::red_black_insertion_template_method::inject_additional_data(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *from,
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *to) const {
    reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(to)->color = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(from)->color;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
typename red_black_tree<tkey, tvalue, tkey_comparer>::color_node red_black_tree<tkey, tvalue, tkey_comparer>::get_color(
        typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *current_node) const noexcept {
    return current_node == nullptr ? color_node::BLACK : current_node->color;
}

// begin region insertion template method

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void red_black_tree<tkey, tvalue, tkey_comparer>::red_black_insertion_template_method::after_insert_inner(
        tkey const &key,
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
        std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive) {
    if (subtree_root_address->left_subtree_address == nullptr &&
        subtree_root_address->right_subtree_address == nullptr) {
        reinterpret_cast<red_black_node *>(subtree_root_address)->color = path_to_subtree_root_exclusive.empty()
                                                                          ? red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK
                                                                          : red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;

        _rise_further_status = _rise_near_status;
        if (!path_to_subtree_root_exclusive.empty()) {
            _rise_near_status =
                    (*path_to_subtree_root_exclusive.top())->left_subtree_address == subtree_root_address
                    ? rise_status::FROM_LEFT_SUBTREE
                    : rise_status::FROM_RIGHT_SUBTREE;
        }

        return;
    }

    switch (_balance_status) {
        case balance_status::NO_BALANCE_NEEDED:
            if (path_to_subtree_root_exclusive.empty()) {
                reinterpret_cast<red_black_node *>(subtree_root_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
            }
            return;
        case balance_status::BALANCE_AT_GP:
            _balance_status = balance_status::BALANCE_AT_P;
            _rise_further_status = _rise_near_status;
            if (!path_to_subtree_root_exclusive.empty()) {
                _rise_near_status =
                        (*path_to_subtree_root_exclusive.top())->left_subtree_address == subtree_root_address
                        ? rise_status::FROM_LEFT_SUBTREE
                        : rise_status::FROM_RIGHT_SUBTREE;
            }

            return;
    }

    red_black_node **parent = nullptr;
    red_black_node *grandson = nullptr;
    red_black_node *uncle = nullptr;

    uncle = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(
            _rise_near_status == rise_status::FROM_LEFT_SUBTREE
            ? subtree_root_address->right_subtree_address
            : subtree_root_address->left_subtree_address);

    parent = _rise_near_status == rise_status::FROM_LEFT_SUBTREE
             ? reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node **>(&subtree_root_address->left_subtree_address)
             : reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node **>(&subtree_root_address->right_subtree_address);

    if (*parent != nullptr) {
        grandson = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(
                _rise_further_status == rise_status::FROM_LEFT_SUBTREE
                ? (*parent)->left_subtree_address
                : (*parent)->right_subtree_address);
    }

    if (_tree->get_color(grandson) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK ||
        _tree->get_color(*parent) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK) {
        _balance_status = balance_status::NO_BALANCE_NEEDED;
        return;
    }

    if (_rise_further_status != _rise_near_status && uncle == nullptr) {
        if (_rise_near_status == rise_status::FROM_LEFT_SUBTREE) {
            _tree->left_rotation(
                    reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **>(parent));
            grandson = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>((*parent)->left_subtree_address);
        } else {
            _tree->right_rotation(
                    reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **>(parent));
            grandson = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>((*parent)->right_subtree_address);
        }
    }

    if (_tree->get_color(uncle) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK) {
        (reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(subtree_root_address))->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;

        if (_rise_near_status == rise_status::FROM_LEFT_SUBTREE) {
            _tree->right_rotation(&subtree_root_address);
        } else {
            _tree->left_rotation(&subtree_root_address);
        }

        (reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(subtree_root_address))->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;

        _balance_status = balance_status::NO_BALANCE_NEEDED;
    } else {
        uncle->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
        (*parent)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
        (reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(subtree_root_address))->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;

        _balance_status = balance_status::BALANCE_AT_GP;
    }

    if (path_to_subtree_root_exclusive.empty()) {
        reinterpret_cast<red_black_node *>(subtree_root_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
    }
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer>::red_black_insertion_template_method::red_black_insertion_template_method(
        red_black_tree<tkey, tvalue, tkey_comparer> *tree)
        : _tree(tree),
          binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method(tree) {
}

// end region insertion template method

// begin region removing template method

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void red_black_tree<tkey, tvalue, tkey_comparer>::red_black_removing_template_method::after_remove_inner(
        tkey const &key,
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
        std::list<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive) {

    if (subtree_root_address == nullptr) {
        return;
    }

    if (!path_to_subtree_root_exclusive.empty()) {
        auto pop_back_list = **path_to_subtree_root_exclusive.rbegin();
        _rise_near_status =
                pop_back_list->left_subtree_address == subtree_root_address
                ? rise_status_remove::FROM_LEFT_SUBTREE
                : rise_status_remove::FROM_RIGHT_SUBTREE;
    }

    if (path_to_subtree_root_exclusive.empty() &&
        subtree_root_address->left_subtree_address == nullptr &&
        subtree_root_address->right_subtree_address == nullptr) {
        return;
    }

    red_black_node **parent = nullptr;
    red_black_node *brother = nullptr;

    parent = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node **>(*path_to_subtree_root_exclusive.rbegin());

    // subtree_root_address = _rise_near_status == rise_status_remove::FROM_LEFT_SUBTREE
    //                            ? (*parent)->left_subtree_address
    //                            : (*parent)->right_subtree_address;

    if (!path_to_subtree_root_exclusive.empty() &&
        _tree->get_color(
                reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(subtree_root_address)) ==
        red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK) {
        if (subtree_root_address == (*parent)->left_subtree_address) {
            brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>((*parent)->right_subtree_address);
            if (_tree->get_color(brother) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED) {
                brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
                (*parent)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;
                _tree->left_rotation(
                        reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **>(parent));

                brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>((*parent)->right_subtree_address);
            }

            if (_tree->get_color(
                    reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(brother->left_subtree_address)) ==
                red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK &&
                _tree->get_color(
                        reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(brother->right_subtree_address)) ==
                red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK) {
                brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;
                subtree_root_address = *parent;
            } else if (_tree->get_color(
                    reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(brother->left_subtree_address)) ==
                       red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK) {
                reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(brother->left_subtree_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
                brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;

                _tree->right_rotation(
                        reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **>(brother));
                brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>((*parent)->right_subtree_address);
            } else {

                brother->color = (*parent)->color;
                (*parent)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
                reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(brother->right_subtree_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
                _tree->left_rotation(
                        reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **>(parent));
                // reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(subtree_root_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
            }
        } else {
            if (subtree_root_address == (*parent)->right_subtree_address) {
                brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>((*parent)->left_subtree_address);
                if (_tree->get_color(brother) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED) {
                    brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
                    (*parent)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;
                    _tree->right_rotation(
                            reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **>(parent));

                    brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>((*parent)->left_subtree_address);
                }

                if (_tree->get_color(
                        reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(brother->right_subtree_address)) ==
                    red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK &&
                    _tree->get_color(
                            reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(brother->left_subtree_address)) ==
                    red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK) {
                    brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;
                    subtree_root_address = *parent;
                } else if (_tree->get_color(
                        reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(brother->left_subtree_address)) ==
                           red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK) {
                    reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(brother->right_subtree_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
                    brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;

                    _tree->left_rotation(
                            reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **>(brother));
                    brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>((*parent)->left_subtree_address);
                } else {

                    brother->color = (*parent)->color;
                    (*parent)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
                    reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(brother->left_subtree_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
                    _tree->right_rotation(
                            reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **>(parent));
                    // reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node *>(subtree_root_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
                }
            }
        }

    }

}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer>::red_black_removing_template_method::red_black_removing_template_method(
        red_black_tree<tkey, tvalue, tkey_comparer> *tree)
        : _tree(tree),
          binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method(tree) {
}

// end region removing template method

// begin region constructor

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer>::red_black_tree(memory *allocator, logger *logger)
        : binary_search_tree<tkey, tvalue, tkey_comparer>(
        new red_black_insertion_template_method(this),
        new typename binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method(this),
        new red_black_removing_template_method(this),
        allocator,
        logger) {
}

// end region constructor

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer>::red_black_tree(
        red_black_tree<tkey, tvalue, tkey_comparer> const &other)
        : red_black_tree(other._allocator, other._logger) {
    binary_search_tree<tkey, tvalue, tkey_comparer>::_root = other.copy();
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer>::red_black_tree(
        red_black_tree<tkey, tvalue, tkey_comparer> &&other) noexcept {
    this->move(static_cast<binary_search_tree<tkey, tvalue, tkey_comparer> &&>(std::move(other)));
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer> &red_black_tree<tkey, tvalue, tkey_comparer>::operator=(
        const red_black_tree<tkey, tvalue, tkey_comparer> &other) {
    if (this == &other) {
        return *this;
    }

    this->clear();

    this->_allocator = other._allocator;
    this->_logger = other._logger;
    this->_root = other.copy();

    return *this;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer> &red_black_tree<tkey, tvalue, tkey_comparer>::operator=(
        red_black_tree<tkey, tvalue, tkey_comparer> &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    this->clear();

    delete this->_insertion;
    delete this->_reading;
    delete this->_removing;

    this->move(std::move(other));

    return *this;

    return *this;
}

#endif // RED_BLACK_TREE_H