# Use a C++ development image
FROM gcc:12.2.0

# Set the working directory
WORKDIR /app

# Copy the entire project
COPY . /app

# Install CMake
RUN apt-get update && apt-get install -y cmake

# Build the project
RUN cmake . && make

# Command to run the application
CMD ["./logger_demo"]