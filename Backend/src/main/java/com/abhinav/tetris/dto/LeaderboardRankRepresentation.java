package com.abhinav.tetris.dto;

public record LeaderboardRankRepresentation(
        Long rank,
        String name,
        Long bestScore
) {
}
