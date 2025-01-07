pipeline { 
    agent {
        docker {
            image 'hh71099/my-image:latest'  // Specify the Docker image
            args '-u root'  // Run as root user inside the container
        }
    }

    environment {
        BUILD_DIR = 'build'  // Directory for build files
        CPP_CHECK_REPORT = 'cppcheck-report.xml'  // Cppcheck output file
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm  // Check out the source code from the repository
            }
        }

        stage('Install Dependencies') {
    steps {
        sh '''
        # Update package list and add missing repositories
        apt-get update && apt-get install -y software-properties-common
        add-apt-repository ppa:ubuntu-sdk-team/ppa -y
        apt-get update

        # Install required packages
        apt-get install -y qtbase5-dev qtchooser qt5-qmake cmake build-essential qt5scxml-dev
        '''
    }
}
        stage('Build') {
            steps {
                script {
                    // Clean and set up the build directory
                    sh '''
                    rm -rf ${BUILD_DIR}   # Remove any existing build directory
                    mkdir ${BUILD_DIR}    # Create a new build directory
                    '''
                }

                // Build the project using build.sh
                sh '''
                chmod +x build.sh       # Ensure the build script is executable
                ./build.sh              # Run the build script
                '''
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
                withEnv(['QT_QPA_PLATFORM=offscreen']) {  // Run tests in offscreen mode
                    sh '''
                    cd ${BUILD_DIR}      # Change to the build directory
                    ./calculator_test    # Run the test executable
                    '''
                }
            }
        }

        stage('Archive Artifacts') {
            steps {
                // Archive build artifacts
                archiveArtifacts artifacts: "${BUILD_DIR}/**", fingerprint: true

                // Publish the static analysis report
                publishHTML([ 
                    allowMissing: true,   // Don't fail if the report is missing
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
            cleanWs()  // Clean the workspace after the build
        }
        success {
            echo 'Build succeeded!'
        }
        failure {
            echo 'Build failed!'
        }
    }
}
