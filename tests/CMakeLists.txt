#每个文件都可以单独作为可执行程序编译
file(GLOB PANS_TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)
#排序
list(SORT PANS_TEST_SOURCES)
#查找线程支持           REQUIRED强制要求
find_package(Threads REQUIRED)
#设置输出路径
set(PANS_TEST_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/tests")
#开始遍历之前加入的所有源文件
foreach(TEST_SOURCE IN LISTS PANS_TEST_SOURCES)
    #NAME_WE只要文件名 不要后缀 不要前面的路径
    get_filename_component(TEST_NAME "${TEST_SOURCE}" NAME_WE)
    #if(TARGET  检测是否已经存在这个名字的目标
    if(TARGET "${TEST_NAME}")
        message(FATAL_ERROR "Cannot creat test target '${TEST_NAME}':a target with that name already exists")
    endif()
    #创建可执行程序 (目标名字 来自哪个文件)
    add_executable("${TEST_NAME}" "${TEST_SOURCE}")
    #(目标 公开度 )
    target_link_libraries("${TEST_NAME}" PRIVATE pans Threads::Threads)
    #设置目标属性  PROPERTIES是分割前面的 目标 和后面的 属性 及其 值
    set_target_properties("${TEST_NAME}" PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PANS_TEST_OUTPUT_DIRECTORY}"
    )
    #遍历 CMAKE_CONFIGURATION_TYPES 列表
    foreach(CONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)
        string(TOUPPER "${CONFIG}" CONFIG_UPPER) #配置名称转换成大写
        set_target_properties("${TEST_NAME}" PROPERTIES
        #Debug 配置下的可执行程序输出目录，设置为 PANS_TEST_OUTPUT_DIRECTORY
            "RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER}" "${PANS_TEST_OUTPUT_DIRECTORY}"
        )
        
    endforeach()

endforeach()
