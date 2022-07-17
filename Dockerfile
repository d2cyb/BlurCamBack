FROM archlinux as base
RUN pacman -Suy --noconfirm
RUN pacman -S --noconfirm opencv cmake make gcc clang valgrind fmt spdlog catch2 qt5-base vtk openmpi glew hdf5
WORKDIR app


FROM base as build
COPY . .
RUN mkdir -p build && cd build && cmake .. && make


FROM scratch as app-export
COPY --from=build /app/build/bin/BlurCamBack /BlurCamBack


FROM build as test
RUN ./build/bin/BlurCamBack_unit
RUN ./build/bin/BlurCamBack_bench
RUN (cd build && ctest -T memcheck)
