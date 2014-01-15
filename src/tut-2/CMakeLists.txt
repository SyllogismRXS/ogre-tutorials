set (APP_NAME tut-2)

file (GLOB SRCS *.cpp)
file (GLOB HDRS *.h)

# Find super class' headers and sources
file (GLOB SUPER_SRCS "../BaseApplication/*.cpp")
file (GLOB SUPER_HDRS "../BaseApplication/*.h")

# Add super class' headers and sources to executable
set( SRCS ${SRCS} ${SUPER_SRCS})
set( HDRS ${HDRS} ${SUPER_HDRS})

add_executable(${APP_NAME} ${HDRS} ${SRCS})

target_link_libraries(${APP_NAME} ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LEAP_LIBS})


# Link executable to other libraries
#target_link_libraries(${APP_NAME})

##--------------------------------------------------------
## Library Creation
##--------------------------------------------------------
#SET (LIBRARY_NAME BHV_Colregs)
#SET (LIB_MAJOR 0)
#SET (LIB_MINOR 0)
#SET (LIB_RELEASE 1)
#
#file( GLOB SRCS *.cpp)
#file( GLOB HDRS *.h)
#
#ADD_LIBRARY(${LIBRARY_NAME} SHARED 
#  ${SRCS}
#  )
#
#TARGET_LINK_LIBRARIES(${LIBRARY_NAME}
#  OTHERLIBS
#  )
#
#SET (_soversion ${LIB_MAJOR}.${LIB_MINOR}.${LIB_RELEASE})
#
#set_target_properties(${LIBRARY_NAME} PROPERTIES SOVERSION ${LIB_MAJOR} VERSION ${_soversion})
#
#INSTALL(TARGETS ${LIBRARY_NAME}
#  LIBRARY DESTINATION lib
#  ARCHIVE DESTINATION lib
#)
