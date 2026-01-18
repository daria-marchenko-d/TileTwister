#!/bin/bash
echo "Running all integration tests for Tile Twister..."
echo "=================================================="
echo ""

# Function to run a test
run_test() {
    local test_name="$1"
    local test_file="$2"
    
    echo "🔍 Test: $test_name"
    echo "------------------------"
    
    if [ -f "build/tests/$test_file.exe" ]; then
        # Run test with quiet mode
        ./build/tests/$test_file.exe --quiet
        
        # Check exit code
        if [ $? -eq 0 ]; then
            echo "✅ PASSED"
        else
            echo "❌ FAILED"
        fi
    else
        echo "⚠️  SKIPPED (file not found)"
    fi
    
    echo ""
}

# Run all tests
run_test "Basic Grid Tests" "test_basic"
run_test "Game Over Tests" "test_gameover"
run_test "Grid+Game Integration" "test_integration_grid_game"
run_test "Game Flow Integration" "test_integration_game_flow"
run_test "Advanced Scenarios" "test_integration_advanced"

echo "=================================================="
echo "All tests completed!"
