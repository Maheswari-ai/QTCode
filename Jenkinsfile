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
        REPO_URL = 'https://code.qt.io/qt/qt5.git'  // Qt5 repository URL
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
                apt-get update
                apt-get install -y qtbase5-dev qtchooser qt5-qmake cmake build-essential git

                # Clone and build Qt5 from source
                if [ ! -d "qt5" ]; then
                    git clone ${REPO_URL} qt5
                fi

                cd qt5
                # Ensure remote URL is set if missing
                git remote add origin ${REPO_URL} || true
                ./init-repository --module-subset=default,-qtwebengine
                
                mkdir qt5-build && cd qt5-build
                ../configure -release -opensource -confirm-license -nomake tests -nomake examples
                make -j$(nproc)
                make install
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
