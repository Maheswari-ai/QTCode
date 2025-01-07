pipeline {
    agent {
        docker {
            image 'hh71099/my-image:latest'  // Docker image you want to use
            // label 'your-label'  // Optional: specify label if needed
            // args '-u 18003:3558'  // Optional: any additional docker run arguments if necessary
        }
    }

    environment {
        BUILD_DIR = 'build'
        CPP_CHECK_REPORT = 'cppcheck-report.xml'
    }

    stages {
        stage('Checkout') {
            steps {
                // Checkout the source code
                checkout scm
            }
        }

        stage('Build') {
            steps {
                // Ensure a clean build directory
                script {
                    // Remove any existing build directory and CMakeCache.txt
                    sh "rm -rf ${BUILD_DIR}"  // Remove any existing build directory
                    sh "rm -f CMakeCache.txt" // Remove any leftover CMake cache file to avoid conflicts
                    sh "mkdir ${BUILD_DIR}"    // Create a new build directory
                }

                // Run the build.sh script (make sure it's executable)
                script {
                    sh 'chmod +x build.sh'  // Ensure build.sh is executable
                    sh './build.sh'         // Run the build.sh script
                }

                // Now, run CMake and Make inside the new build directory
                dir("${BUILD_DIR}") {
                    sh '''
                        cmake ..  // Configure the project with CMake
                        make      // Build the project using make
                    '''
                }
            }
        }

        stage('Static Analysis') {
            steps {
                // Run Cppcheck for static analysis
                sh '''
                    cppcheck --enable=all --inconclusive --xml --xml-version=2 \
                    --output-file=${CPP_CHECK_REPORT} .
                '''
            }
        }

        stage('Test') {
            steps {
                // Set QT_QPA_PLATFORM to offscreen to run tests without a display
                withEnv(['QT_QPA_PLATFORM=offscreen']) {
                    sh '''
                        cd build
                        ./calculator_test  // Run the test executable
                    '''
                }
            }
        }

        stage('Archive Artifacts') {
            steps {
                // Archive build artifacts
                archiveArtifacts artifacts: "${BUILD_DIR}/**", fingerprint: true

                // Archive static analysis report
                publishHTML([ 
                    allowMissing: false,
                    alwaysLinkToLastBuild: false,
                    keepAll: true,
                    reportDir: '.',
                    reportFiles: "${CPP_CHECK_REPORT}",
                    reportName: "Cppcheck Report"
                ])
            }
        }
    }

    post {
        always {
            // Clean up workspace after the build
            cleanWs()
        }
        success {
            echo 'Build succeeded!'
        }
        failure {
            echo 'Build failed!'
        }
    }
}
