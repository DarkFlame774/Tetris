package com.abhinav.tetris.dto;

import java.time.LocalDateTime;

public record HealthResponse(
        String status,
        LocalDateTime timestamp
) {
}
