/*
*
*   This is a source code file implementing incrementor related methods
*   Depends on incrementor.h
*
*/
#include <godot_cpp/core/class_db.hpp>

#include "incrementor.h"
#include "big_number.h"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/variant/variant.hpp"

using namespace godot;

// ============== Constructor / Destructor ============== //
Incrementor::Incrementor() {
    increment = Ref<BigNumber>();
}

Incrementor::~Incrementor() { }

// =================== Member Methods =================== //
void Incrementor::set_increment(const godot::Ref<BigNumber> &value){
    if (value.is_null()) {
        increment = Ref<BigNumber>(); // Clear to null reference
        return;
    }

    
};
godot::Ref<BigNumber> Incrementor::get_increment() const {return increment;};

// ========== Bind Member Methods / Properties ========== //
void Incrementor::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_increment", "value"), &Incrementor::set_increment);
    ClassDB::bind_method(D_METHOD("get_increment"), &Incrementor::get_increment);
    ADD_PROPERTY(PropertyInfo(Variant::NIL, "increment"), "set_increment", "get_increment");
}

