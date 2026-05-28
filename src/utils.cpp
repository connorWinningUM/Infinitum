#include "utils.h"

namespace utils {

    bool is_BigNumber(const godot::Variant &p_other) {
        godot::Object *raw_obj = p_other;

        if (raw_obj != nullptr && raw_obj->get_class() == "BigNumber")
            return true;

        return false;
    }
}
