pipeline {
    agent any

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
                    sh "rm -rf ${BUILD_DIR}"
                    sh "mkdir ${BUILD_DIR}"
                }
                
                // Build with CMake
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
                // Run Cppcheck for static analysis
                sh '''
                    cppcheck --enable=all --inconclusive --xml --xml-version=2 \
                    --output-file=${CPP_CHECK_REPORT} .
                '''
            }
        }

        stage('Test') {
            steps {
                script {
                sh 'Xvfb :99 & export DISPLAY=:99'
                sh '''
                    cd build
                    ./calculator_test
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

