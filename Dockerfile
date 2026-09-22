# CampusGuard Docker Image
# Provides a reproducible build/run environment with g++, make, gdb, and valgrind.

FROM ubuntu:22.04

# Install build and debugging tools
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        g++ \
        make \
        gdb \
        valgrind && \
    rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy all source and project files into the image
COPY . .

# Compile the project using the Makefile
RUN make

# Run the CampusGuard demonstration on container start
CMD ["./CampusGuard"]
