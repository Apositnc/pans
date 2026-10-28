#搜索所有源文件和头文件 在指定目录里面搜索
file(GLOB_RECURSE PANS_SOURCES CONFIGURE_DEPENDS *.cpp *.cc *.c)
file(GLOB_RECURSE PANS_HEADERS CONFIGURE_DEPENDS *.h *.hpp)

#用接收到的源文件建立静态库 pans
add_library(pans STATIC ${PANS_SOURCES})

#去哪里找头文件
target_include_directories(pans 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include># 只在构建阶段生效公共去include里面
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>#安装后去哪里找
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src#私有的src里面还有 .h文件
)

#挂上cmake文件夹里面的参数设置
target_link_libraries(pans PUBLIC pans_options)

#添加额外的设置
target_compile_options(pans PRIVATE
    # 主库可能需要更严格的警告
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
        -Werror               # 将警告视为错误 (主库严格要求)
    >
)

#安装到哪里
install(TARGETS pans
    EXPORT pansTargets#将 pans 加入一个叫 pansTargets 的导出集合
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}#不同类型安装到不同目录里面
)
install(FILES ${PANS_HEADERS}#头文件列表里面的每一个都复制到下面这个路径
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pans
)
