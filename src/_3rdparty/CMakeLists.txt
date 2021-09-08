set (HAVAL_SOURCES
	haval.c
	haval.h
)

add_library (haval ${HAVAL_SOURCES})
set_target_properties (haval PROPERTIES LINKER_LANGUAGE C)
