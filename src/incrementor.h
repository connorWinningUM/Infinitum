/*
*
*   This header holds the class for an incrementor
*
*   Incrementors uses a reference to a bigNumber and increments it
*   in a Godot thread
*
*/
#pragma once
#include "big_number.h"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/variant.hpp>

class Incrementor: public godot::RefCounted {
    GDCLASS(Incrementor, godot::RefCounted)

protected:
    static void _bind_methods();

public:
    Incrementor();
    ~Incrementor();

    void set_increment(const godot::Ref<BigNumber> &value);
    godot::Ref<BigNumber> get_increment() const;
    
private:
    godot::Ref<BigNumber> increment;

};
