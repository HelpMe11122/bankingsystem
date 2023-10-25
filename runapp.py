import subprocess

# Build the program using g++
build_command = "g++ -o myprogram main.cpp -lsqlite3"
build = subprocess.run(build_command, shell=True, capture_output=True, text=True)

# Check for build errors
if build.returncode != 0:
    print("Build failed:")
    print(build.stderr)
else:
    print("Build successful.")
    
    # Run the program
    run_command = "./myprogram"
    run = subprocess.run(run_command, shell=True, capture_output=True, text=True)

    # Print the output of the program
    print("Program Output:")
    print(run.stdout)
