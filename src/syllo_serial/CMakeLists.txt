#--------------------------------------------------------
# Library Creation
#--------------------------------------------------------
SET (LIBRARY_NAME syllo_serial)
SET (LIB_MAJOR 0)
SET (LIB_MINOR 0)
SET (LIB_RELEASE 1)

file( GLOB SRCS *.cpp)
file( GLOB HDRS *.h)

ADD_LIBRARY(${LIBRARY_NAME} SHARED 
  ${SRCS}
  )

TARGET_LINK_LIBRARIES(${LIBRARY_NAME}
  #OTHERLIBS
  )

SET (_soversion ${LIB_MAJOR}.${LIB_MINOR}.${LIB_RELEASE})

set_target_properties(${LIBRARY_NAME} PROPERTIES SOVERSION ${LIB_MAJOR} VERSION ${_soversion})

INSTALL(TARGETS ${LIBRARY_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
