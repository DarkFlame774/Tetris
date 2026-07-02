package com.abhinav.tetris.dto;

public record LeaderboardEntityRepresentation(
        Long id,
        String name,
        Long bestScore
) {
}
