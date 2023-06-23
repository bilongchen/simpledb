add_library(
    simpledb_record
    OBJECT
    rid.cpp
)

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:simpledb_record>
    PARENT_SCOPE
)
