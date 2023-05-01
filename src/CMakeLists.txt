find_packages(fmt spdlog absl glm stb Threads)
include_third_parties()

add_executable(
    main
        main.cpp
        image/image.h image/image.cpp
        objects/object.h objects/object.cpp
        objects/sphere.h objects/sphere.cpp
        renderer/ray.h renderer/ray.cpp renderer/camera.h renderer/camera.cpp
)
target_link_libraries(
    main
    PRIVATE project_options
            project_warnings
    PRIVATE fmt::fmt
            spdlog::spdlog
            absl::base
            stb::stb
            glm::glm
            Threads::Threads
)
target_compile_options(
    main
    PRIVATE -DSTB_IMAGE_WRITE_IMPLEMENTATION
)
target_compile_options(
    main
    PRIVATE -Wno-padded -Wno-misc-no-recursion
)
