pipeline {
    agent any

    environment {
        BUILD_DIR = 'build'
        CPP_CHECK_REPORT = 'cppcheck-report.xml'
    }

    stages {
        stage('Checkout') {
            steps {
                // Checkout the source code from GitHub
                checkout scm
            }
        }

        stage('Setup Environment') {
            steps {
                // Install necessary dependencies
                sh '''
                sudo apt-get update
                sudo apt-get install -y build-essential qt5-default cmake cppcheck
                '''
            }
        }

        stage('Build') {
            steps {
                // Create a clean build directory and build the project
                script {
                    sh "rm -rf ${BUILD_DIR}"
                    sh "mkdir ${BUILD_DIR}"
                }
                dir("${BUILD_DIR}") {
                    sh '''
                        cmake ..
                        make
                    '''
                }
            }
        }

        stage('Static Analysis') {
            steps {
                // Run Cppcheck on source files
                sh '''
                    cppcheck --enable=all --inconclusive --xml --xml-version=2 \
                    --output-file=${CPP_CHECK_REPORT} calculator.cpp calculator.h \
                    calculator_logic.cpp statemachine.cpp statemachine.h
                '''
            }
        }

        stage('Test') {
            steps {
                // Run tests
                sh '''
                    cd ${BUILD_DIR}
                    ./calculator_test
                '''
            }
        }

        stage('Archive Artifacts') {
            steps {
                // Archive build artifacts and reports
                archiveArtifacts artifacts: "${BUILD_DIR}/**", fingerprint: true
                publishHTML([
                    allowMissing: false,
                    alwaysLinkToLastBuild: false,
                    keepAll: true,
                    reportDir: ".",
                    reportFiles: "${CPP_CHECK_REPORT}",
                    reportName: "Cppcheck Report"
                ])
            }
        }
    }

    post {
        always {
            // Clean workspace after build
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

